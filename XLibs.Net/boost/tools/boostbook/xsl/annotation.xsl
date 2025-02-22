<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
  <xsl:key name="classes" match="class|struct|union" use="@name"/>
  <xsl:key name="methods" match="method|overloaded-method" use="@name"/>
  <xsl:key name="functions" match="function|overloaded-function" use="@name"/>
  <xsl:key name="libraries" match="library" use="@name"/>
  <xsl:key name="macros" match="macro" use="@name"/>
  <xsl:key name="headers" match="header" use="@name"/>

  <xsl:template match="classname" mode="annotation">
    <!-- Determine the (possibly qualified) class name we are looking for -->
    <xsl:variable name="fullname">
      <xsl:choose>
        <xsl:when test="@alt">
          <xsl:value-of select="@alt"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="string(.)"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <!-- Strip off any instantiation -->
    <xsl:variable name="name">
      <xsl:choose>
        <xsl:when test="contains($fullname, '&lt;')">
          <xsl:value-of select="substring-before($fullname, '&lt;')"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$fullname"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <!-- Determine the unqualified name -->
    <xsl:variable name="unqualified-name">
      <xsl:call-template name="strip-qualifiers">
        <xsl:with-param name="name" select="$name"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:call-template name="cxx-link-name">
      <xsl:with-param name="lookup" select="."/>
      <xsl:with-param name="type" select="'class'"/>
      <xsl:with-param name="name" select="$name"/>
      <xsl:with-param name="display-name" select="string(.)"/>
      <xsl:with-param name="unqualified-name" select="$unqualified-name"/>
      <xsl:with-param name="nodes" select="key('classes', $unqualified-name)"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template match="methodname" mode="annotation">
    <!-- Determine the (possibly qualified) method name we are looking for -->
    <xsl:variable name="fullname">
      <xsl:choose>
        <xsl:when test="@alt">
          <xsl:value-of select="@alt"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="string(.)"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <!-- Strip off any call -->
    <xsl:variable name="name">
      <xsl:choose>
        <xsl:when test="contains($fullname, '(')">
          <xsl:value-of select="substring-before($fullname, '(')"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$fullname"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <!-- Determine the unqualified name -->
    <xsl:variable name="unqualified-name">
      <xsl:call-template name="strip-qualifiers">
        <xsl:with-param name="name" select="$name"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:call-template name="cxx-link-name">
      <xsl:with-param name="lookup" select="."/>
      <xsl:with-param name="type" select="'method'"/>
      <xsl:with-param name="name" select="$name"/>
      <xsl:with-param name="display-name" select="string(.)"/>
      <xsl:with-param name="unqualified-name" select="$unqualified-name"/>
      <xsl:with-param name="nodes" select="key('methods', $unqualified-name)"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template match="functionname" mode="annotation">
    <!-- Determine the (possibly qualified) function name we are
         looking for -->
    <xsl:variable name="fullname">
      <xsl:choose>
        <xsl:when test="@alt">
          <xsl:value-of select="@alt"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="string(.)"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <!-- Strip off any call -->
    <xsl:variable name="name">
      <xsl:choose>
        <xsl:when test="contains($fullname, '(')">
          <xsl:value-of select="substring-before($fullname, '(')"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$fullname"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <!-- Determine the unqualified name -->
    <xsl:variable name="unqualified-name">
      <xsl:call-template name="strip-qualifiers">
        <xsl:with-param name="name" select="$name"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:call-template name="cxx-link-name">
      <xsl:with-param name="lookup" select="."/>
      <xsl:with-param name="type" select="'function'"/>
      <xsl:with-param name="name" select="$name"/>
      <xsl:with-param name="display-name" select="string(.)"/>
      <xsl:with-param name="unqualified-name" select="$unqualified-name"/>
      <xsl:with-param name="nodes" 
        select="key('functions', $unqualified-name)"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template match="libraryname" mode="annotation">
    <xsl:variable name="name">
      <xsl:choose>
        <xsl:when test="@alt">
          <xsl:value-of select="@alt"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="text()"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="node" select="key('libraries', $name)"/>
    
    <xsl:choose>
      <xsl:when test="count($node)=0">
        <xsl:message>
          <xsl:text>warning: Cannot find library '</xsl:text>
          <xsl:value-of select="$name"/>
          <xsl:text>'</xsl:text>
        </xsl:message>
        <xsl:value-of select="$name"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:call-template name="library.link">
          <xsl:with-param name="node" select="$node"/>
          <xsl:with-param name="name" select="text()"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="conceptname" mode="annotation">
    <xsl:param name="name" select="text()"/>

    <xsl:call-template name="concept.link">
      <xsl:with-param name="name" select="$name"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template match="macroname" mode="annotation">
    <xsl:param name="name" select="text()"/>
    
    <xsl:variable name="node" select="key('macros', $name)"/>
    <xsl:choose>
      <xsl:when test="count($node) = 0">
        <xsl:message>
          <xsl:text>warning: cannot find macro `</xsl:text>
          <xsl:value-of select="$name"/>
          <xsl:text>'</xsl:text>
        </xsl:message>
        <xsl:value-of select="$name"/>
      </xsl:when>

      <xsl:when test="count($node) = 1">
        <xsl:call-template name="internal-link">
          <xsl:with-param name="to">
            <xsl:call-template name="generate.id">
              <xsl:with-param name="node" select="$node"/>
            </xsl:call-template>
          </xsl:with-param>
          <xsl:with-param name="text" select="$name"/>
        </xsl:call-template>
      </xsl:when>

      <xsl:otherwise>
        <xsl:message>
          <xsl:text>error: macro `</xsl:text>
          <xsl:value-of select="$name"/>
          <xsl:text>' is multiply defined.</xsl:text>
        </xsl:message>
        <xsl:value-of select="$node"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="headername" mode="annotation">
    <xsl:param name="name" select="text()"/>
    
    <xsl:variable name="node" select="key('headers', $name)"/>
    <xsl:choose>
      <xsl:when test="count($node) = 0">
        <xsl:message>
          <xsl:text>warning: cannot find header `</xsl:text>
          <xsl:value-of select="$name"/>
          <xsl:text>'</xsl:text>
        </xsl:message>
        <xsl:value-of select="$name"/>
      </xsl:when>

      <xsl:when test="count($node) = 1">
        <xsl:call-template name="internal-link">
          <xsl:with-param name="to">
            <xsl:call-template name="generate.id">
              <xsl:with-param name="node" select="$node"/>
            </xsl:call-template>
          </xsl:with-param>
          <xsl:with-param name="text" select="$name"/>
        </xsl:call-template>
      </xsl:when>

      <xsl:otherwise>
        <xsl:message>
          <xsl:text>error: header `</xsl:text>
          <xsl:value-of select="$name"/>
          <xsl:text>' is multiply defined.</xsl:text>
        </xsl:message>
        <xsl:value-of select="$node"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="text()" mode="annotation">
    <xsl:param name="highlight" select="false()"/>
    <xsl:choose>
      <xsl:when test="$highlight">
        <xsl:call-template name="source-highlight">
          <xsl:with-param name="text" select="."/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:copy-of select="."/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="code" mode="annotation">
    <computeroutput>
      <xsl:apply-templates mode="annotation"/>
    </computeroutput>
  </xsl:template>

  <xsl:template match="node()" mode="annotation">
    <xsl:param name="highlight" select="false()"/>
    <xsl:element name="{name(.)}">
      <xsl:for-each select="./@*">
        <xsl:attribute name="{name(.)}">
          <xsl:value-of select="."/>
        </xsl:attribute>
      </xsl:for-each>
      <xsl:apply-templates select="./*|./text()" mode="annotation">
        <xsl:with-param name="highlight" select="$highlight"/>
      </xsl:apply-templates>
    </xsl:element>
  </xsl:template>

  <!-- The "purpose" mode strips simpara/para elements so that we can
       place the resulting text into a comment in the synopsis. -->
  <xsl:template match="para|simpara" mode="purpose">
    <xsl:apply-templates mode="annotation"/>
  </xsl:template>

  <xsl:template match="*" mode="purpose">
    <xsl:apply-templates select="." mode="annotation"/>
  </xsl:template>

  <xsl:template match="text()" mode="purpose">
    <xsl:apply-templates select="." mode="annotation"/>
  </xsl:template>
</xsl:stylesheet>
