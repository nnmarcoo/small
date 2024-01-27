#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

InputBox, html , Input Emoji HTML, , , A_ScreenWidth // 10, A_ScreenHeight // 10, , , Locale, ,
links := {}
names := {}

if (html = "")
    ExitApp
else if ErrorLevel
    ExitApp
if (SubStr(html, Strlen(html)-1) = "32")
    size := "32"
else
    size := "128"

While (InStr(html, "?") != 0)
{
    links.Push(subStr(html, InStr(html, "src=")+5, InStr(html, "?")-InStr(html, "src=")-5))
    names.Push(subStr(html, InStr(html, "alt=")+6, InStr(html, ":""")-InStr(html, "alt=")-6))
    html := SubStr(html, InStr(html, "?")+1)
}
server := SubStr(names[1], InStr(names[1], ">", false, 1, 6)+1, InStr(names[1], "</", false, 1, 5)-InStr(names[1], ">", false, 1, 6)-1)
links.RemoveAt(1)
names.RemoveAt(1)

FileCreateDir, Emojis\%server%
max := names.MaxIndex()
Gui, Add, Progress, w200 h20 cBlue vprogress Range0-%max%, 0
Gui, -Caption +AlwaysOnTop
Gui, Show
Loop % names.MaxIndex()
{
    GuiControl,, progress, +1
    file := links[A_Index] "?size=" size "&amp;quality=lossless"
    dest := StrReplace("Emojis\" server "\" names[A_Index] SubStr(links[A_Index], InStr(links[A_Index], ".", false, 1, 3)), ".webp", ".png")
    UrlDownloadToFile, %file%, %dest%
}
ExitApp
Return

Esc::
ExitApp
Return