


; doesn't work

#Requires AutoHotkey v2.0
#SingleInstance Force
SetWorkingDir "C:\Users\marco\AppData\Roaming\Spotify"
spotify := "spotify.exe"

Loop {
    if (PID := ProcessExist(spotify)) {
        title := WinGetTitle("ahk_pid" PID)
        if (!InStr(title, " - ") && !InStr(title, "Spotify Free")) { 
            WinClose(title)
            WinWaitClose(title)
            Sleep 500
            Run spotify

            WinWait("Spotify Free")
            
            PID := ProcessExist(spotify)
            title := WinGetTitle("ahk_pid" PID)
            
            ControlSend("^{NumpadRight}", , title)
            Sleep 500
            ControlSend("{Space}", , title)
        }
    }
    Sleep 1000
}