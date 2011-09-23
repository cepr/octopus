##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Compass
ConfigurationName      :=Debug
IntermediateDirectory  :=../../out/$(ProjectName)/$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/cedric/octopus/src"
ProjectPath            := "/home/cedric/octopus/src/robots/Compass"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Cédric
Date                   :=18/09/2011
CodeLitePath           :="/home/cedric/.codelite"
LinkerName             :=avr-g++
ArchiveTool            :=avr-ar rcus
SharedObjectLinkerName :=avr-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=avr-g++
C_CompilerName         :=avr-gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).out
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/cedric/octopus/src/robots/Compass/Compass.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             :=-Wall -Os -fno-exceptions -fno-threadsafe-statics -ffunction-sections -fdata-sections -fshort-enums -mmcu=atmega328p -DF_CPU=8000000L  $(Preprocessors)
C_CmpOptions           :=-Wall -Os -fno-exceptions -fno-threadsafe-statics -ffunction-sections -fdata-sections -fshort-enums -mmcu=atmega328p -DF_CPU=8000000L  $(Preprocessors)
LinkOptions            := -Os -Wl,--gc-sections -mmcu=atmega328p -Wl,-Map=$(OutDir)/$(ProjectName).map -Wl,--script=$(WorkspacePath)/ldscripts/ldscript_atmega328p.x 
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)$(WorkspacePath)/libs/avr $(IncludeSwitch)$(WorkspacePath)/libs/common $(IncludeSwitch)$(WorkspacePath)/libs/sensors 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)OctopusAVR 
LibPath                := $(LibraryPathSwitch)$(WorkspacePath)/out/OctopusAVR/$(ConfigurationName) 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
LC_MESSAGES:=en_EN.UTF-8
Objects=$(IntermediateDirectory)/Compass$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)
	@echo Executing Post Build commands ...
	avr-objcopy -O ihex -R .eeprom $(OutDir)/$(ProjectName).out $(OutDir)/$(ProjectName).hex
	@echo Done

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

makeDirStep:
	@test -d ../../out/$(ProjectName)/$(ConfigurationName) || $(MakeDirCommand) ../../out/$(ProjectName)/$(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Compass$(ObjectSuffix): Compass.cpp $(IntermediateDirectory)/Compass$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cedric/octopus/src/robots/Compass/Compass.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Compass$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Compass$(DependSuffix): Compass.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Compass$(ObjectSuffix) -MF$(IntermediateDirectory)/Compass$(DependSuffix) -MM "/home/cedric/octopus/src/robots/Compass/Compass.cpp"

$(IntermediateDirectory)/Compass$(PreprocessSuffix): Compass.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Compass$(PreprocessSuffix) "/home/cedric/octopus/src/robots/Compass/Compass.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Compass$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Compass$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Compass$(PreprocessSuffix)
	$(RM) $(OutputFile)


