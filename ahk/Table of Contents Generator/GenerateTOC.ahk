#Requires AutoHotkey v2.0
#SingleInstance Force

root := FileSelect("D")
readme := "-----------`n### Table of Contents`n`n"

Loop Files, root "\*.*", "R" {
    folder := SubStr(A_LoopFileDir, InStr(A_LoopFileDir, "\",,,-1)+1)
    
}




FileAppend readme, "TOC.md"