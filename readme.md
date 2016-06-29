# This simple test shows crazyness of DBCS processing in Windows console

## Non-DBCS enabled OS (EU, US, RU, etc).

### Raster font is selected in console

* Console can't store or show any characters out of OEM CP. So all CJK glyphs will be displayed as `?`.
* One (broken) CJK glyph takes one cell, so 78 CJK glyphs take same space as 78 ASCII chars.

![screens/non-dbcs-raster.png](https://github.com/Maximus5/Write-Read-Test/raw/master/screens/non-dbcs-raster.png)

### TTF font is selected in console

* Console is working in Unicode mode and **can** store Unicode codepoints, and may display them, if you have configured FontLink.
* One CJK glyph also takes one cell, so 78 CJK glyphs take same space as 78 ASCII chars.

![screens/non-dbcs-unicode.png](https://github.com/Maximus5/Write-Read-Test/raw/master/screens/non-dbcs-unicode.png)

## DBCS enabled OS (Chinese, Japanese, etc).

The crazyness begins. I tested CP 936.

* Console is able to store large set of characters, because CP 936 is double byte character set, and therefore this CP covers wide set of Unicode codepoint.
* NB, doesn't matter what font is selected in console.

### Raster font is selected in console

* One CJK glyph is **displayed** in place of **two cells**.
* Unicode console API returns each CJK in **one** `CHAR_INFO` and do not use `COMMON_LVB_LEADING_BYTE` and `COMMON_LVB_TRAILING_BYTE` flags.
* If console application tries to write more than (console_width/2) CJK glyphs, the string is automatically **folded to next line**.

![screens/dbcs-raster.png](https://github.com/Maximus5/Write-Read-Test/raw/master/screens/dbcs-raster.png)

### TTF font is selected in console

* Same as above, one CJK glyph is **displayed** in place of **two cells**.
* But Unicode console API returns each CJK as **two** consecutive `CHAR_INFO` first with `COMMON_LVB_LEADING_BYTE` (0x100) and second with `COMMON_LVB_TRAILING_BYTE` (0x200) flags.
* Same as above, if console application tries to write more than (console_width/2) CJK glyphs, the string is automatically **folded to next line**.

![screens/dbcs-unicode.png](https://github.com/Maximus5/Write-Read-Test/raw/master/screens/dbcs-unicode.png)

## Bottom line

How it can be bearable?
