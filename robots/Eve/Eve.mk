##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Eve
ConfigurationName      :=Debug
IntermediateDirectory  :=../../out/$(ProjectName)/$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/cedric/octopus/git/octopus"
ProjectPath            := "/home/cedric/octopus/git/octopus/robots/Eve"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Cédric
Date                   :=18/06/2012
CodeLitePath           :="/home/cedric/.codelite"
LinkerName             :=avr-g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=avr-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
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
ObjectsFileList        :="/home/cedric/octopus/git/octopus/robots/Eve/Eve.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             :=-Wall -Os -fno-exceptions -fno-threadsafe-statics -ffunction-sections -fdata-sections -fshort-enums -mmcu=atmega328p -DF_CPU=8000000L  $(Preprocessors)
C_CmpOptions           :=-Wall -Os -fno-exceptions -fno-threadsafe-statics -ffunction-sections -fdata-sections -fshort-enums -mmcu=atmega328p -DF_CPU=8000000L  $(Preprocessors)
LinkOptions            := -Os -Wl,--gc-sections -mmcu=atmega328p -Wl,-Map=$(OutDir)/$(ProjectName).map -Wl,--script=$(WorkspacePath)/ldscripts/ldscript_atmega328p.x 
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)$(WorkspacePath)/libs/avr $(IncludeSwitch)$(WorkspacePath)/libs/common 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)OctopusAVR 
LibPath                := $(LibraryPathSwitch)$(WorkspacePath)/out/OctopusAVR/$(ConfigurationName) 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
LC_MESSAGES:=en_EN.UTF-8
Objects=$(IntermediateDirectory)/Eve$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d ../../.build-debug/OctopusAVR $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

../../.build-debug/OctopusAVR:
	@echo stam > "../../.build-debug/OctopusAVR"




PostBuild:
	@echo Executing Post Build commands ...
	avr-objcopy -O ihex -R .eeprom $(OutDir)/$(ProjectName).out $(OutDir)/$(ProjectName).hex
	@echo Done

$(IntermediateDirectory)/.d:
	@test -d ../../out/$(ProjectName)/$(ConfigurationName) || $(MakeDirCommand) ../../out/$(ProjectName)/$(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Eve$(ObjectSuffix): Eve.cpp 
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cedric/octopus/git/octopus/robots/Eve/Eve.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Eve$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Eve$(PreprocessSuffix): Eve.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Eve$(PreprocessSuffix) "/home/cedric/octopus/git/octopus/robots/Eve/Eve.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Eve$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Eve$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Eve$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/cedric/octopus/git/octopus/.build-debug/Eve"


