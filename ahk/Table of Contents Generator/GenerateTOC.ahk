#Requires AutoHotkey v2.0
#SingleInstance Force

root := FileSelect("D")
readme := "-----------`n### Table of Contents`n`n"
folders := []

Loop Files, root "\*.*", "R" {
    folder := SubStr(A_LoopFileDir, InStr(A_LoopFileDir, "\",,,-1)+1)
    if (InStr(A_LoopFileDir, "\."))
        continue
    if (!has(folders, folder))
        msgbox folder
    
    folders.Push(folder)
    
}

FileAppend readme, "TOC.md"
Return

has(haystack, needle) {
    if (!isObject(haystack))
        return false
    if (haystack.Length == 0)
        return false
    for k, v in haystack
        if (v == needle)
            return true
    return false
}