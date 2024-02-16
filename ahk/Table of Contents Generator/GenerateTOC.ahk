#Requires AutoHotkey v2.0
#SingleInstance Force

root := FileSelect("D")
readme := "-----------`n### Table of Contents`n"
folders := []

Loop Files, root "\*.*", "R" {
    folder := SubStr(A_LoopFileDir, InStr(A_LoopFileDir, "\",,,-1)+1)
    if (has(folders, folder))
        continue
    if (InStr(A_LoopFileDir, "\."))
        continue
    
    readme .= "`n[" folder "](" A_LoopFileDir ")`n" 
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