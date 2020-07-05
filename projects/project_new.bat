@set /P project_name="Enter Project Name:"

@IF EXIST %project_name% (
	@echo [ERROR] This project has already been created
	@PAUSE
	@exit -1
)

@echo [INFO] Creating project structure
@mkdir %project_name%
@mkdir %project_name%\resources
@mkdir %project_name%\sources

@echo [INFO] Copying Game resources
@copy ..\engine\misc\Project_main %project_name%\sources\main.cpp
@copy ..\engine\resources\mont.otf %project_name%\resources\mont.otf

@echo [INFO] configuring Unix build system
@echo GAME_TITLE := %project_name%> %project_name%\ProjectConfig.mk
@powershell.exe -Command "get-content ..\engine\misc\Project_Config" >> %project_name%\ProjectConfig.mk 
@copy ..\engine\misc\Project_Makefile %project_name%\Makefile
@copy ..\engine\misc\Project_gitignore %project_name%\.gitignore

@echo [INFO] configuring Windows build system

@set sln_cmd="Get-Content ..\engine\misc\Project_Solution | %%{$_ -replace 'TemplateProject','%project_name%'}"
@echo %sln_cmd%
@powershell.exe -Command %sln_cmd% > %project_name%\%project_name%.sln

@set proj_cmd="Get-Content ..\engine\misc\Project_vcxproj | %%{$_ -replace 'TemplateProject','%project_name%'}"
@echo %proj_cmd%
@powershell.exe -Command %proj_cmd% > %project_name%\%project_name%.vcxproj

@copy ..\engine\misc\Project_vcxproj_filters %project_name%\%project_name%.vcxproj.filters

@echo [INFO] Done!
@PAUSE


