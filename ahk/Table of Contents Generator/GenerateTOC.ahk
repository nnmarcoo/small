#Requires AutoHotkey v2.0
#SingleInstance Force

root := FileSelect("D")

Loop Files, root "\*.*", "R"
    MsgBox A_LoopFileDir