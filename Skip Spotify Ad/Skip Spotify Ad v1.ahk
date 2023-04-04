#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir, C:\Users\marco\AppData\Roaming\Spotify  ; Ensures a consistent starting directory.

processName := "spotify.exe"
Loop {
    WinGetTitle, title, ahk_exe %processName%
    if !(title = "Spotify Free") {
        if (InStr(title, "-") = 0) {
            Sleep, 1000
            WinGetTitle, title, ahk_exe %processName%
            if (InStr(title, "-") = 0) {
                Process, Close, spotify.exe
                Sleep, 2000
                Run, spotify.exe
                Sleep, 4000
                WinGetTitle, title, ahk_exe %processName%
                ControlSend,, ^{NumpadRight}, %title%
                Sleep, 500
                ControlSend,, {Space}, %title%
            }
        }
    }
    Sleep, 1000
}