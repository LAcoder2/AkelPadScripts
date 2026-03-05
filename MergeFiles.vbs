Option Explicit

' Запуск в VBS:
'Set Args = WScript.Arguments
'If Args.Count < 3 Then
'    WScript.Echo "Usage: script.vbs ""FolderPath"" ""*.ext *.ext2"""
'    Exit Sub 'WScript.Quit
'End If
'MergeTextFiles  Args(0), Args(1), Args(2)

Public Stream, initFlg

main() ' запус в VBS

Private Sub main()
    Dim SrcPath, DstPath, Mask, Dlm, FldrName, oShell, oFolder
    
    Set oShell = CreateObject("shell.application")
    
    Set oFolder = oShell.BrowseForFolder(0, "Выберите папку из которой нужно собрать текстовые файлы", &H8090, 0)
    If oFolder Is Nothing Then MsgBox "Папка источника не выбрана! Скрипт будет завершен.": Exit Sub
    SrcPath = oFolder.Self.Path
    
    Set oFolder = oShell.BrowseForFolder(0, "Выберите папку в которую будут записаны файлы с собранной информацией", &H8090, 0)
    If oFolder Is Nothing Then MsgBox "Папка назначения не выбрана! Скрипт будет завершен.": Exit Sub
    DstPath = oFolder.Self.Path 'SrcPath & "\tmp"
    
    Mask = InputBox("Введите маску для отбора собираемых файлов по маске", , "*.js;*.vbs;*.txt")            '"*.js;*.vbs"
    ' Заменяем пробелы в масках на ; для корректной работы Filter (если требуется)
'    Mask = Replace(Mask, " ", ";")

    Dlm = InputBox("Введите разделитель через который будут сшиваться собираетмые файлы", , "-|#|#|#|#|-")  'vbCrLf & "-|#|#|#|#|-" & vbCrLf
    If Len(Dlm) Then Dlm = vbCrLf & Dlm & vbCrLf
    
    MergeTextFiles SrcPath, Mask, Dlm, DstPath
End Sub

'Private Sub Test_MergeTextFiles()
'    MergeTextFiles "F:\PortableProgs\AkelPadPortable\App\AkelPadx64\AkelFiles\Plugs\Scripts\tmp", _
'                  "*.js;*.vbs", _
'                  vbCrLf & "-|#|#|#|#|-" & vbCrLf, _
'                  "F:\PortableProgs\AkelPadPortable\App\AkelPadx64\AkelFiles\Plugs\Scripts\tmp\tmp"
'End Sub

'Основная процедура
Private Sub MergeTextFiles(SrcPath, Mask, Dlm, DstPath)
    Dim FSO 'As FileSystemObject
    Set FSO = CreateObject("Scripting.FileSystemObject")
    Dim Shell: Set Shell = CreateObject("Shell.Application")
    Dim StmA: Set StmA = CreateObject("ADODB.Stream")
    With StmA
      .Mode = 3: .Open
      .Charset = "x-ansi": .WriteText " " 'Для блокировки записи UTF16-BOM
      .Position = 0: .Charset = "Unicode" 'Приходится записывать в начале один пробел, и ставить курсор на 1
      .Position = 1
    End With
    Dim StmU8: Set StmU8 = CreateObject("ADODB.Stream")
    With StmU8
      .Mode = 3: .Open: .Charset = "UTF-8"
      .WriteText " ": .Position = 3 'Для записи UTF8-BOM
    End With
    
    ' Получаем объект папки (абсолютный путь)
    Dim Folder: Set Folder = Shell.Namespace(SrcPath) 'FSO.GetAbsolutePathName(SrcPath))
    If Folder Is Nothing Then Exit Sub 'WScript.Quit
    
    Dim Items: Set Items = Folder.Items()
    ' 192 = 64 (SHCONTF_NONFOLDERS) + 128 (SHCONTF_INCLUDEHIDDEN)
    Items.Filter 192, Mask
    If Items.Count = 0 Then Exit Sub 'WScript.Quit
    
    Dim utf8BOM: utf8BOM = ChrB(&HEF) & ChrB(&HBB) & ChrB(&HBF)
    Dim utf16BOM: utf16BOM = &HFEFF
    Dim nullChar: nullChar = ChrB(0)
    Dim DlmU8: DlmU8 = ToUTF8(Dlm)
    Dim DlmA: DlmA = ToANSI(Dlm)
    
    ' Перебираем отфильтрованные файлы
    Dim posU8, posA, File 'As folderitem2
    
    For Each File In Items
        ' Читаем файл как текст (ANSI по умолчанию в FSO)
        Dim ts 'As TextStream
        Set ts = FSO.OpenTextFile(File.Path, 1, False, -1)
        Dim sTmp: sTmp = ts.ReadAll()
        ts.Close
        Dim fName: fName = File.Name & Chr(13) & Chr(10) 'vbCrLf
        
        If InStrB(1, LeftB(sTmp, 10), nullChar) Then  'если файл в UTF16
            With StmU8
              SelectCharset StmU8, "UTF-8"            'переключаем в режим UTF-8
              .WriteText fName
              If AscW(sTmp) = utf16BOM Then           'если UTF16-BOM
                  .WriteText Mid(sTmp, 2)
              Else
                  .WriteText sTmp
              End If
              .WriteText Dlm
            End With
        ElseIf InStrB(1, LeftB(sTmp, 3), utf8BOM) Then 'если UTF8
            With StmU8
              SelectCharset StmU8, "UTF-8"
              .WriteText fName
              
              SelectCharset StmU8, "Unicode"          'переключаем в режим UTF-16
              .WriteText MidB(sTmp, 4)                'записываем с пропуском BOM
              .WriteText DlmU8
            End With
        Else                                          'если ANSI
            'Здесь можно добавить обработку UTF8 без BOM и прочие форматы
            Dim pos
            With StmA
              SelectCharset StmA, "x-ansi"
              .WriteText fName
              
              SelectCharset StmA, "Unicode"
              .WriteText sTmp
              .WriteText DlmA
            End With
        End If
    Next
    
    Dim FldrName: FldrName = GetFolderName(SrcPath)
    
    With StmA
      .Position = 0: .Type = 1
      .SaveToFile DstPath & "\" & FldrName & "Ansi.txt", 2
      .Close
    End With
    With StmU8
      .Position = 0: .Type = 1
      .SaveToFile DstPath & "\" & FldrName & "Utf8.txt", 2
      .Close
    End With
End Sub
Sub SelectCharset(oStream, Charset)
    Dim pos
    With oStream
      If .Charset <> Charset Then _
          pos = .Position: .Position = 0: .Charset = Charset: .Position = pos:
    End With
End Sub
Function GetFolderName(FldrPath)
    Dim pos
    pos = InStrRev(FldrPath, "\")
    GetFolderName = Mid(FldrPath, pos + 1)
End Function
Private Sub TestToANSI()
    Dim s: s = "Какая-то строка!"
    Dim s2: s2 = ToANSI(s)
'    Debug.Print StrConv(s2, vbUnicode)
End Sub
Function ToANSI(u16Text)
    If initFlg Then
    Else
        Set Stream = CreateObject("ADODB.Stream")
        Stream.Mode = 3
        initFlg = True
    End If
    With Stream
      .Open
      .Type = 2
      .Charset = "x-ansi"
      .WriteText u16Text
      .Position = 0
      .Type = 1
      ToANSI = CStr(.Read)
      .Close
    End With
End Function
Function FromAnsi(ansiText)
    If initFlg Then
    Else
        Set Stream = CreateObject("ADODB.Stream")
        Stream.Mode = 3
        initFlg = True
    End If
    With Stream
      .Open
      .Type = 2
      .Charset = "Unicode"
      .WriteText ansiText
      .Position = 0
      .Charset = "x-ansi"
      .Position = 2 'Пропускаем Utf16-BOM (FF FE)
      FromAnsi = .ReadText
      .Close
    End With
End Function
Function ToUTF8(u16Text)
    If initFlg Then
    Else
        Set Stream = CreateObject("ADODB.Stream")
        Stream.Mode = 3
        initFlg = True
    End If
    With Stream
      .Open
      .Type = 2
      .Charset = "UTF-8"
      .WriteText u16Text
      .Position = 0
      .Type = 1
      .Position = 3
      ToUTF8 = CStr(.Read)
      .Close
    End With
End Function
Function FromUTF8(u8Text)
    If initFlg Then
    Else
        Set Stream = CreateObject("ADODB.Stream")
        Stream.Mode = 3
        initFlg = True
    End If
    With Stream
      .Open
      .Type = 2
      .Charset = "Unicode"
      .WriteText u8Text
      .Position = 0
      .Charset = "UTF-8"
      .Position = 2
      FromUTF8 = .ReadText
      .Close
    End With
End Function
'Конвертирует строку в массив байтов
Function StringToBytes(Text)
    If initFlg Then
    Else
        Set Stream = CreateObject("ADODB.Stream")
        Stream.Mode = 3
        initFlg = True
    End If
    With Stream
      .Open
      .Type = 2
      .Charset = "Unicode"
      .WriteText Text
      .Position = 0
      .Type = 1
      .Position = 2
      StringToBytes = .Read
      .Close
    End With
End Function