<?xml version="1.0" encoding="utf-8"?> 
<xsl:stylesheet version="1.0" 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
    <html>
    <body>
    <h2>Element Database by atomic number </h2>
    <table border="1">
        <tr bgcolor="#9acd32">
	    <th>Atmoic Number</th>
	    <th>Abbreviation</th>
	    <th>Atomic Mass</th>
	    <th>Name</th>
	</tr>
	<xsl:for-each select="element-db/element">
	<xsl:sort select="number" data-type="number"/>
	<tr>
	    <td><xsl:value-of select="number"/></td>
	    <td><xsl:value-of select="abbrev"/></td>
	    <td><xsl:value-of select="mass"/></td>
	    <td><xsl:value-of select="name"/></td>
	</tr>
	</xsl:for-each>
    </table>
    </body>
    <body>
    <h2>Element Database by abbreviation </h2>
    <table border="1">
        <tr bgcolor="#9acd32">
	    <th>Abbreviation</th>
	    <th>Name</th>
	    <th>Atomic Number</th>
	    <th>Atomic Mass</th>
	</tr>
	<xsl:for-each select="element-db/element">
	<xsl:sort select="abbrev"/>
	<tr>
	    <td><xsl:value-of select="abbrev"/></td>
	    <td><xsl:value-of select="name"/></td>
	    <td><xsl:value-of select="number"/></td>
	    <td><xsl:value-of select="mass"/></td>
	</tr>
	</xsl:for-each>
    </table>
    </body>
    </html>
</xsl:template>
</xsl:stylesheet>