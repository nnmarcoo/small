#Requires AutoHotkey v2.0
#SingleInstance Force
SetWorkingDir "C:\Users\marco\AppData\Roaming\Spotify"
spotify := "spotify.exe"
delay := 500 ; may need to change on slower PCs

Loop {
    if (PID := ProcessExist(spotify)) {
        try {
            title := WinGetTitle("ahk_pid" PID)
            if (!InStr(title, " - ") && !InStr(title, "Spotify Free")) { 
                WinClose(title)
                WinWaitClose(title)
                Sleep delay
                Run spotify

                WinWait("Spotify Free")

                PID := ProcessExist(spotify)
                title := WinGetTitle("ahk_pid" PID)

                ControlSend("^{NumpadRight}", , title)
                Sleep delay
                ControlSend("{Space}", , title)
                Sleep delay * 8
            }
        }
    }
    Sleep delay * 2
}