:: ===========================================================================
:: Developer/s: Gerardo Tordoya
:: Description: This batch file allows you to create a folder that can only be
::              opened with a password.
::              https://www.wikihow.com/Lock-a-Folder-Using-a-Batch-File
:: Create Date: 2021-09-11
:: Update Date: 2023-06-30
:: ===========================================================================

CLS
@ECHO OFF

TITLE Casillero de carpeta

IF EXIST "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B30309D}" GOTO AbrirCandado
IF NOT EXIST Casillero GOTO CrearCasillero

:Confirmar
    ECHO Cerrar Casillero (carpeta)? (S/N)

    SET/P "respuesta=>"

    IF %respuesta%==S GOTO CerrarCandado
    IF %respuesta%==s GOTO CerrarCandado
    IF %respuesta%==n GOTO Finalizar
    IF %respuesta%==N GOTO Finalizar

    ECHO Ingreso inválido.
    GOTO Confirmar

:CerrarCandado
    REN Casillero "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B30309D}"
    ATTRIB +h +s "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B30309D}"
    ECHO Casillero (carpeta) cerrado.
    GOTO Finalizar

:AbrirCandado
    ECHO Ingrese llave (password) de candado para abrir casillero (carpeta):
    SET/P "password=>"

    :: Reemplazar XXX por la contraseña que desee
    IF NOT %password%==XXX GOTO Fallo

    ATTRIB -h -s "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B30309D}"
    REN "Control Panel.{21EC2020-3AEA-1069-A2DD-08002B30309D}" Casillero
    ECHO Casillero (carpeta) abierto.
    GOTO Finalizar

:Fallo
    ECHO Llave (password) incorrecta.
    GOTO Finalizar

:CrearCasillero
    MD Casillero
    ECHO Casillero (carpeta) creado.
    GOTO Finalizar

:Finalizar
    ECHO Finalizando...
    TIMEOUT /T 2 /NOBREAK > NUL
    EXIT /B 1
