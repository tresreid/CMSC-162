<?xml version="1.0" encoding="utf-8"?> 
      <xsl:stylesheet version="1.0" 
          xmlns:xsl="http://www.w3.org/1999/XSL/Transform"> 
	  <xsl:output method="test"/>

	  <xsl:template name="newline"> 
	      <xsl:text>&#0010;</xsl:text> 
 `	  </xsl:template>

 	  <xsl:template match="/"> 
	      <xsl:apply-templates select="//particle"/> 
	  </xsl:template>

	  <xsl:template match="particle"> 
	      <xsl:text>Element: </xsl:text>
	      <xsl:value-of select="."/> 
	      <xsl:call-template name="newline"/> 
	  </xsl:template>

	  
</xsl:stylesheet>