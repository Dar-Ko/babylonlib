###############################################################################
# Test plugin for Pluma
# Test 3: Run Pluma with debug:
# G_MESSAGES_DEBUG=all pluma 2>&1 | grep -i "test\|plugin\|peas\|error"
# Open Pluma and go to Edit > Preferences > Plugins > check Test22.
#
# There are two different plugin systems:
# Old (before MATE 2.0): Use Pluma.WindowActivatable and property window of 
#  type Pluma.Window.
# New (MATE 2.0+): Use Peas.Activatable and property object of type 
#  GObject.Object (but when used with Pluma, it will be a Pluma.Window).

import sys
print('DEBUG:', sys.version) # Python 2.7

import gi
gi.require_version('Gtk'  , '3.0')
gi.require_version('Pluma', '1.0')

from gi.repository import GObject, Gtk, Pluma  # Pluma

# Try to import Peas for new style
try:
    gi.require_version('Peas', '1.0')
    from gi.repository import Peas
    HAS_PEAS = True
except:
    HAS_PEAS = False

print('DEBUG: Peas is available :=', HAS_PEAS)

###############################################################################
# Debugging helper examines the type of the window
def is_pluma_window(window):
    # Check if it's a Pluma.Window
    if not isinstance(window, Pluma.Window):
        # Try to cast it (for debugging)
        print(f"DEBUG: Object type: {type(window)}")
        print(f"DEBUG: Object attributes: {dir(window)[:10]}...")

        if hasattr(window, 'get_title'):
            print(f"DEBUG: Has get_title method, assuming it's a window")
        else:
            print(f"ERROR: Not a Pluma.Window and missing window methods")
            return False
    else:
        print(f"INFO: Confirmed Pluma.Window: Title = '{window.get_title()}'")
    return True

###############################################################################
# Common functionality for both plugin styles
class TestPluginCommon:
    def _real_activate(self):
        print('DEBUG: TestPlugin _real_activate:', self.window)

        # Debugging: check if self.window is a Pluma.Window
        is_pluma_window(self.window)

    def _real_deactivate(self):
        print('DEBUG: TestPlugin _real_deactivate:', self.window)

    def _real_update_state(self):
        print('DEBUG: TestPlugin _real_update_state:', self.window)
        pass

###############################################################################
# Define the plugin class conditionally
if HAS_PEAS and not hasattr(Pluma, 'WindowActivatable'):
    print('DEBUG: Using Peas for new (Ubuntu 24.04) style')
    class TestPlugin(GObject.Object, Peas.Activatable, TestPluginCommon):
        __gtype_name__ = "TestPluginPeas"
        object = GObject.Property(type=GObject.Object)

        def __init__(self):
            GObject.Object.__init__(self)
            self.window = None
            print('DEBUG: __init__: ', self.__gtype_name__)

        def do_activate(self):
            # In the new style, the window is passed as self.object
            self.window = self.object
            self._real_activate()
        
        def do_deactivate(self):
            self._real_deactivate()
            self.window = None
        
        def do_update_state(self):
            self._real_update_state()
            pass
else:
    # Old style plugin with Pluma
    print('DEBUG: Using Pluma old style')
    class TerminalPlugin(GObject.Object, Pluma.WindowActivatable, TestPluginCommon):
        __gtype_name__ = "TestPluginPluma"
        window = GObject.Property(type=Pluma.Window)
        
        def __init__(self):
            GObject.Object.__init__(self)
            print('DEBUG: __init__: ', self.__gtype_name__)

        def do_activate(self):
            self._real_activate()
        
        def do_deactivate(self):
            self._real_deactivate()
        
        def do_update_state(self):
            self._real_update_state()
            pass

