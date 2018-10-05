; Этот файл содержит в себе определения для доступа к параметрам содержищимся в заголовке FAT16 файловой системы
%ifndef FAT_DEF
%define FAT_DEF 

%define bsOemName       bp+0x03  ; 8  ; OEM название
%define bsBytesPerSec   bp+0x0B  ; dw ; кол-во байт в секторе
%define bsSecsPerClust  bp+0x0D  ; db ; секторов/кластер
%define bsResSectors    bp+0x0E  ; dw ; кол-во зарез. секторов
%define bsFATs          bp+0x10  ; db ; кол-во таблиц fat
%define bsRootDirEnts   bp+0x11  ; dw ; кол-во папок в корне ФС
%define bsSectors       bp+0x13  ; dw ; кол-во секторов
%define bsMedia         bp+0x15  ; db ; дескриптор медиа
%define bsSecsPerFat    bp+0x16  ; dw ; кол-во секторов в таблице fat
%define bsSecsPerTrack  bp+0x18  ; dw ; кол-во секторов в дорожке
%define bsHeads         bp+0x1A  ; dw ; кол-во головок
%define bsHidden        bp+0x1C  ; dd ; кол-во скрытых секторов
%define bsSectorHuge    bp+0x20  ; dd ; кол-во секторов для больших разделов
%define bsDriveNumber   bp+0x24  ; dw ; номер диска
%define bsSigniture     bp+0x26  ; db ; сигнатура
%define bsVolumeSerial  bp+0x27  ; dd ; серийный номер устройства
%define bsVolumeLabel   bp+0x2B  ; 11 ; метка тома
%define bsSysID         bp+0x36  ; 8  ; системный номер устройства

%endif