#!/usr/bin/env python
# -*- coding: utf8 -*-
# Text Wrap Pluma Plugin
#
# This plugin is intended to ease the setting of Text Wrap (aka Line Wrap,
# Word Wrap) by either a Keyboard Shortcurt (currently sticked to Shift-Ctrl-B),
# a new entry in the View Menu or by an Icon in the Toolbar. The use of either
# option works as a toggle (de- or activate text wrap). The initial setting for
# new or new opened files is taken from the setting in the Preferences dialog
# and remembered per file as long thew file is open.

# Copyright (C) 2008-2009 Christian Hartmann <christian.hartmann@berlin.de>
#               2026 Darko Kolaković


# Import basic requisites
import gi
gi.require_version('Gtk'  , '3.0')
gi.require_version('Pluma', '1.0')

from gi.repository import GObject, Gtk, Pluma  # Pluma

# Try to import Peas for the new style
try:
    gi.require_version('Peas', '1.0')
    from gi.repository import Peas
    HAS_PEAS = True
except:
    HAS_PEAS = False

# for the texts in the UI elements we use gettext (do we really?)
from gettext import gettext as _


# a common ui definition for menu and toolbar additions
ui_str = """<ui>
  <menubar name="MenuBar">
    <menu name="ViewMenu" action="View">
      <placeholder name="ViewOps_2">
        <menuitem name="ToggleTextWrap" action="ToggleTextWrap" />
      </placeholder>
    </menu>
  </menubar>
  <toolbar name="ToolBar">
    <separator />
    <toolitem name="ToggleTextWrap" action="ToggleTextWrap" />
  </toolbar>
</ui>
"""

###############################################################################
# Define the plugin helper class
class ToggleTextWrapHelper:

    # Plugin name constant
    PLUGIN_NAME = "TextWrap"

    def __init__(self, plugin, window):

        self._DEBUG = False # True / False
        self._TRACE('Peas is available :=', HAS_PEAS)
        self._TRACE(plugin.__gtype_name__ ,"created for", window)

        self._window = window
        self._plugin = plugin

        # Define default initial state for the plugin
        _initial_toggle_state_default = True

        # Get initial state from word wrapping in this view (not available
        # on pluma startup, but if plugin is enabled during the pluma session)
        self._TRACE(f"\t_window type: {type(self._window)}")
        _active_view = self._window.get_active_view()
        try:
            self._TRACE(f"\t_active_view type: {type(_active_view)}")
            #_current_wrap_mode = _active_view.get_wrap_mode()
            _current_wrap_mode = self.get_current_wrap_mode()
            if _current_wrap_mode == Gtk.WrapMode.NONE:
                self._initial_toggle_state = False
            else:
                self._initial_toggle_state = True
            self._TRACE(f"\t_initial_toggle_state = {self._initial_toggle_state}")

        except Exception as e:
            self._TRACE(f"\tException: {e}")
            self._TRACE(f"\t_active_view = {_active_view}")
            self._initial_toggle_state = _initial_toggle_state_default
            self._TRACE(f"\tDefault _initial_toggle_state = {self._initial_toggle_state}")

        # Add "Toggle Text Wrap" to the View menu and to the Toolbar
        self._insert_ui_items()

    def get_current_wrap_mode(self):
        # Retrieve a list of all views in the window
        views = self._window.get_views()

        if not views:
            self._TRACE("\tNo views found in window.")
            return None

        # Often the first view in a single-tab scenario,
        # but you can use get_active_view() inside a loop if needed
        active_view = self._window.get_active_view()

        if active_view:
            return active_view.get_wrap_mode()

        # Fallback: if active_view is None but views exist, use the first one
        return views[0].get_wrap_mode()

    def deactivate(self):
        self._TRACE("deactivate", self._window)
        self._remove_ui_items()
        self._window = None
        self._plugin = None


    def _insert_ui_items(self):
        # Get the GtkUIManager
        self._manager = self._window.get_ui_manager()
        # Create a new action group
        self._action_group = Gtk.ActionGroup("PluginActions")

        ## LEFT IN AS AN EXAMPLE:
        ## Create a toggle action (the classic way) ...
        #self._toggle_linebreak_action = gtk.ToggleAction(name="ToggleTextWrap", label="Text Wrap", tooltip="Toggle Current Text Wrap Setting", stock_id=gtk.STOCK_EXECUTE)
        #self._toggle_linebreak_action = gtk.ToggleAction(name="ToggleTextWrap", label="Text Wrap", tooltip="Toggle Current Text Wrap Setting", file="gtk-execute.png")
        ## connect my callback function to the action ...
        #self._toggle_linebreak_action.connect("activate", self.on_toggle_linebreak)
        ## and add the action with Ctrl+Shift+L as its keyboard shortcut
        #self._action_group.add_action_with_accel(self._toggle_linebreak_action, "<Ctrl><Shift>B")
        ## END OF EXAMPLE CODE

        # Create a toggle action (convenience way: see 16.1.2.2. in PyGTK Manual)
        #gtk.STOCK_INSERT_CROSS_REFERENCE
        #gtk.STOCK_INSERT-CROSS-REFERENCE
        #gtk.STOCK_INSERT_FOOTNOTE
        #None
        self._action_group.add_toggle_actions([(
                "ToggleTextWrap",
                Gtk.STOCK_OK,
                _("Text Wrap"),
                "<Ctrl><Shift>B",
                _("Toggle Current Text Wrap Setting"),
                self.on_toggle_linebreak, self._initial_toggle_state)])
        # Insert the action group
        self._manager.insert_action_group(self._action_group, -1)
        # Add my item to the "Views" menu and to the Toolbar
        self._ui_id = self._manager.add_ui_from_string(ui_str)
        # Debug merged ui
        self._TRACE("_insert_ui_items:\n",self._manager.get_ui())


    def _remove_ui_items(self):
        # Remove the ui
        self._manager.remove_ui(self._ui_id)
        self._ui_id = None
        # Remove action group
        self._manager.remove_action_group(self._action_group)
        self._action_group = None
        # ensure that manager updates
        self._manager.ensure_update()

    # This will be triggered on tab switch
    def update_ui(self):
        self._action_group.set_sensitive(self._window.get_active_document() != None)
        self._TRACE("update_ui ", self._window)
        try:
            # Get initial state from word wrapping in this view (if any)
            _active_view = self._window.get_active_view()
            _current_wrap_mode = _active_view.get_wrap_mode()
            self._TRACE(f"\tcurrent_wrap_mode = {_current_wrap_mode}")
            # Get our action and set state according to current wrap mode
            _current_action = self._action_group.get_action("ToggleTextWrap")
            if _current_wrap_mode == Gtk.WrapMode.NONE:
                _current_action.set_active(False)
            else:
                _current_action.set_active(True)
        except Exception as e:
            self._TRACE(f"\tException: {e}")
            return


    def on_toggle_linebreak(self, action):
        self._TRACE("Action in ", self._window)
        _active_view = self._window.get_active_view()
        _current_wrap_mode = _active_view.get_wrap_mode()
        self._TRACE(f"\tcurrent_wrap_mode = {_current_wrap_mode}")
        _current_action = self._action_group.get_action("ToggleTextWrap")
        _is_active = _current_action.get_active()
        self._TRACE("\tcurrent action state = ", _is_active)
        if _is_active:
            _active_view.set_wrap_mode(Gtk.WrapMode.WORD)
        else:
            _active_view.set_wrap_mode(Gtk.WrapMode.NONE)


    # The first argument 's' represents 'self'
    # If debug is True, self.log becomes a printing function.
    # If False, it becomes a lambda that does nothing.
    _TRACE = lambda s, *args: print(f"[{s.PLUGIN_NAME}]:", *args) if s._DEBUG else (lambda *args: None)


###############################################################################
# Define the plugin derivate class
class ToggleTextWrapPlugin(GObject.Object, Pluma.WindowActivatable):
    __gtype_name__ = "ToggleTextWrapPlugin"
    window = GObject.Property(type=Pluma.Window)

    def __init__(self):
        #self.window = self.object #DK
        GObject.Object.__init__(self)
        self._instances = {}


    def do_activate(self):
        self._instances[self.window] = ToggleTextWrapHelper(self, self.window)

        # Manually listen for tab changes since do_update_ui failed DK
        self.window.connect("active-tab-changed", self.on_tab_changed)

    def do_deactivate(self):
        self._instances[self.window].deactivate()
        del self._instances[self.window]
        self.window = None #DK

    # You must define this method to avoid the AttributeError
    def on_tab_changed(self, window, tab):
        self._instances[self.window]._TRACE(f"Tab changed to: {tab}")
        # You can call your UI update logic here manually
        self.do_update_ui()

    def do_update_ui(self):
        self._instances[self.window]._TRACE("do_update_ui", self.window)
        self._instances[self.window].update_ui()

    def update_ui(self):
        self._instances[self.window]._TRACE("update_ui", self.window)
        self._instances[self.window].update_ui()

###############################################################################
# $Log
#  2026-02-01 added _TRACE method for easier debug tracing  DK
#             fixed on_update_ui that was not called on tab changes  DK
#  2026-01-15 adapted the code to work with pluma v1.26.1 on MATE v24.04 DK
# $
# * 2009-04-26:
#   0.2 changed filenames from textwrap to TextWrap as it conflicts with
#   /usr/lib/python2.6/textwrap.py when loading the plugin. Unfortunately
#   i have no real clue what actually is causing this conflict. This might
#   be reasoned by a change in the Gedit Python Plugin Loader, as this has
#   not been happening before upgrading pluma or a prerequisite of it through
#   an upgrade of my Ubuntu to 8.10 or 9.04. Added a couple documents mainly
#   to ease the burden of installation for pluma plugin beginners and made it
#   public available on my company website: http://hartmann-it-design.de/pluma
#   Ref.: https://github.com/infirit/pluma-plugins/blob/master/Textwrap/TextWrap
# * 2008-10-10:
#   0.1 initial release for private use only
# * # This file is (was) part of the Text Wrap Plugin for Gedit

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Parts of this plugin are based on the work of Mike Doty <mike@psyguygames.com>
# who wrote the infamous SplitView plugin. The rest is inspired from the Python
# Plugin Howto document and the Python-GTK documentation.

