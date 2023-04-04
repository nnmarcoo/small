#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
Setformat, float, 0.5	

;======================
NUMBER_OF_CASES := 100
;======================



again:
loop %NUMBER_OF_CASES% {
    Random, out , 0, 1000000
    if (out < 2557.5)
        knife += 1
    else if (out < 6393.9)
        red += 1
    else if (out < 31969.3)
        pink += 1
    else if (out < 159846.5)
        purple += 1
    else if (out < 799232.7)
        blue += 1
}
total += Round(NUMBER_OF_CASES*2.7)
totalknives += knife
msgbox % "Total Money Spent: $" total "`nTotal Knives: " totalknives "`n`nKnives: " knife "`nReds: " red "`nPinks: " pink "`nPurples: " purple "`nBlues: " blue
knife := 0
red := 0
pink := 0
purple := 0
blue := 0
goto, again
Return
Esc::
ExitApp