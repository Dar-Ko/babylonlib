<?xml version="1.0" ?>
<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html"
              version="1.0"
              encoding="utf-8"
              doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
              doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
              indent="yes"/>

  <xsl:template match="/">

    <xsl:for-each select="rss">
      <xsl:for-each select="channel">

        <!-- html xmlns:xsl="http://www.w3.org/TR/WD-xsl" -->
        <html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
          <head>
            <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
            <!-- Channel title -->
            <title><xsl:value-of select="title" /></title>
            <link rel="stylesheet" type="text/css" href="TestIndex.css" />
          </head>
          <body>

            <h2><xsl:value-of select="title" /></h2>
            <p><xsl:value-of select="description" /></p>
            <hr />

            <xsl:for-each select="item">
              <xsl:variable name="href"><xsl:value-of select="link" /></xsl:variable>
              <xsl:variable name="title"><xsl:value-of select="title" /></xsl:variable>

              <p>
              <table border="0" width="60%">
              <!-- Item title -->
              <tr><th colspan="2" align="left"><xsl:value-of select="title" /></th></tr>
              <tr>
                <td width="40%">
                  <a href="{$href}" title="{$title}">
                    <xsl:value-of select="link" />
                  </a>
                </td>
                <td width="60%"><xsl:value-of select="description" /></td>
              </tr>
              </table>
              </p>
            </xsl:for-each>

            <hr />
          </body>
        </html>

      </xsl:for-each> <!-- channel -->
    </xsl:for-each> <!-- rss -->

  </xsl:template>
</xsl:stylesheet>
