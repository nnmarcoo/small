#Requires AutoHotkey v2.0
#SingleInstance Force
SetWorkingDir "C:\Users\<USER>\AppData\Roaming\Spotify"
spotify := "spotify.exe"
nosong := "Spotify Free"
delay := 500 ; may need to change on slower PCs

; TODO: fix possible error where spotify doesn't respond

Loop {
    if (PID := ProcessExist(spotify)) {
        try {
            active := WinExist("A")
            title := WinGetTitle("ahk_pid" PID)
            if (!InStr(title, " - ") && !InStr(title, nosong)) { 
                WinClose(title)
                WinWaitClose(title)
                Sleep delay
                Run spotify

                WinWait(nosong)

                WinMoveBottom(nosong)

                ControlSend("^{NumpadRight}", , nosong)
                Sleep delay
                ControlSend("{Space}", , nosong)
                Sleep delay / 2
                WinActivate(active)
                Sleep delay * 8
            }
        }
    }
    Sleep delay * 2
}