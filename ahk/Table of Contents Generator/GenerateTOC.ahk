#Requires AutoHotkey v2.0
#SingleInstance Force

root := FileSelect("D")
readme := "-----------`n### Table of Contents`n"
folders := []
bullets := ["","*","-"]

Loop Files, root "\*.*", "R" {
    folder := getname(A_LoopFileDir)
    if (has(folders, folder) || InStr(A_LoopFileDir, "\."))
        continue

    distance := getdistance(A_LoopFileDir, root)
    readme .= "`n[" folder "](" StrReplace(SubStr(A_LoopFileDir, StrLen(root)+2), " ", "%20") ")`n" 
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

getname(path) {
    return SubStr(path, InStr(path, "\",,,-1)+1)
}

getdistance(path, root) {
    count := 0
    fromroot := SubStr(path, StrLen(root)+1)
    Loop parse, fromroot, "\"
        count++
    return count-1 
}