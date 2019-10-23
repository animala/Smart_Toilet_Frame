#================================================================
# DebugFactory Builder make file
#
# Copyright  : Panasonic Corporation
#================================================================

#================================================================
# DebugFactory Builder makefile variables
#
# PROJECT    : target file name 
# CC         : compiler name
# ASM        : assembler name
# LINK       : linker name
# LIBTOOL    : library tool name
# CINC       : include file paths (for compiler)
# AINC       : include file paths (for assembler)
# LIBPATH    : library file paths
# LIBFILES   : library names
# CFLAGS     : compiler options
# AFLAGS     : assembler options
# CAFLAGS    : assembler options via compiler
# LFLAGS     : linker options
# LBFLAGS    : library tool options
# OBJ_DIR    : object file output folder
# OBJ_EXT    : object file extension
#================================================================

#================================================================
# Variable assignment
#================================================================
!include Smart_Toilet.pathmacro
PROJECT = Smart_Toilet.ex
CC = CC101.EXE
ASM = AS101.EXE
LINK = LD101.EXE
LIBTOOL = SLIB101.EXE
CINC =\
	-IC:\PROGRA~2\Panasonic\DFBuilder5\BuiltInCC\CC101\2_0R5\INCLUDE \
	-I..\System_files \
	-I..\HARDWEAR \
	-I.
AINC =\
	-I..\System_files \
	-I..\HARDWEAR \
	-I.
LIBFILES =\
	-lC:\PROGRA~2\Panasonic\DFBuilder5\BuiltInCC\CC101\2_0R5\LIB\CC101.LIB \
	-l.\panax_ex_mon101e.l
CFLAGS = -c -fenable-asm -fc9x-comment -fchar-bfield -flong-bfield -funsigned-bfield -w -e -g -D__USE_MONITOR_EXLIB -march=AM13E
AFLAGS = -g -j -D__USE_MONITOR_EXLIB 
CAFLAGS = -Ot -ZC -Zv12 -g -j -D__USE_MONITOR_EXLIB 
LFLAGS =  -g -m -e
LBFLAGS =  -c
OBJ_DIR = .\\
OBJ_EXT = .rf


SOURCEFILE =\
	.\Main1.c \
	..\System_files\MN101AF50D.asm \
	..\HARDWEAR\Init_all.c \
	.\TM1629.c \
	..\HARDWEAR\Moto_deal.c \
	..\HARDWEAR\IR.c \
	..\HARDWEAR\Function_deal.c \
	..\HARDWEAR\ADC.c \
	..\HARDWEAR\Rolling.c \
	..\HARDWEAR\Pump_pwm.c \
	..\HARDWEAR\Instant_heat.c \
	..\HARDWEAR\Cover_Circle.c \

OBJFILES =\
	$(OBJ_DIR)Main1$(OBJ_EXT) \ 
	$(OBJ_DIR)MN101AF50D$(OBJ_EXT) \ 
	$(OBJ_DIR)Init_all$(OBJ_EXT) \ 
	$(OBJ_DIR)TM1629$(OBJ_EXT) \ 
	$(OBJ_DIR)Moto_deal$(OBJ_EXT) \ 
	$(OBJ_DIR)IR$(OBJ_EXT) \ 
	$(OBJ_DIR)Function_deal$(OBJ_EXT) \ 
	$(OBJ_DIR)ADC$(OBJ_EXT) \ 
	$(OBJ_DIR)Rolling$(OBJ_EXT) \ 
	$(OBJ_DIR)Pump_pwm$(OBJ_EXT) \ 
	$(OBJ_DIR)Instant_heat$(OBJ_EXT) \ 
	$(OBJ_DIR)Cover_Circle$(OBJ_EXT) \ 


#================================================================
# Link
#================================================================
$(PROJECT): $(OBJFILES)
#=========================PRELINK_S==============================
#=========================PRELINK_E==============================
	$(LINK) @&&|
		-o.\$(PROJECT)
		$(LFLAGS)
		-T@CODE=4000
		-T@DATA=0
		$(OBJ_DIR)MN101AF50D$(OBJ_EXT)
		$(OBJ_DIR)Main1$(OBJ_EXT)
		$(OBJ_DIR)Init_all$(OBJ_EXT)
		$(OBJ_DIR)TM1629$(OBJ_EXT)
		$(OBJ_DIR)Moto_deal$(OBJ_EXT)
		$(OBJ_DIR)IR$(OBJ_EXT)
		$(OBJ_DIR)Function_deal$(OBJ_EXT)
		$(OBJ_DIR)ADC$(OBJ_EXT)
		$(OBJ_DIR)Rolling$(OBJ_EXT)
		$(OBJ_DIR)Pump_pwm$(OBJ_EXT)
		$(OBJ_DIR)Instant_heat$(OBJ_EXT)
		$(OBJ_DIR)Cover_Circle$(OBJ_EXT)
		$(LIBFILES)
|
#================================================================
#	File Format Conversion
#================================================================
	EXCV101.EXE  .\$(PROJECT)

#================================================================
# Assemble, Compile
#================================================================
$(OBJ_DIR)Main1$(OBJ_EXT): .\Main1.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) .\Main1.c
$(OBJ_DIR)MN101AF50D$(OBJ_EXT): ..\System_files\MN101AF50D.asm
	$(ASM)  $(AFLAGS) $(AINC) -o $(OBJ_DIR)$(@F) ..\System_files\MN101AF50D.asm
$(OBJ_DIR)Init_all$(OBJ_EXT): ..\HARDWEAR\Init_all.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) ..\HARDWEAR\Init_all.c
$(OBJ_DIR)TM1629$(OBJ_EXT): .\TM1629.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) .\TM1629.c
$(OBJ_DIR)Moto_deal$(OBJ_EXT): ..\HARDWEAR\Moto_deal.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) ..\HARDWEAR\Moto_deal.c
$(OBJ_DIR)IR$(OBJ_EXT): ..\HARDWEAR\IR.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) ..\HARDWEAR\IR.c
$(OBJ_DIR)Function_deal$(OBJ_EXT): ..\HARDWEAR\Function_deal.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) ..\HARDWEAR\Function_deal.c
$(OBJ_DIR)ADC$(OBJ_EXT): ..\HARDWEAR\ADC.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) ..\HARDWEAR\ADC.c
$(OBJ_DIR)Rolling$(OBJ_EXT): ..\HARDWEAR\Rolling.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) ..\HARDWEAR\Rolling.c
$(OBJ_DIR)Pump_pwm$(OBJ_EXT): ..\HARDWEAR\Pump_pwm.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) ..\HARDWEAR\Pump_pwm.c
$(OBJ_DIR)Instant_heat$(OBJ_EXT): ..\HARDWEAR\Instant_heat.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) ..\HARDWEAR\Instant_heat.c
$(OBJ_DIR)Cover_Circle$(OBJ_EXT): ..\HARDWEAR\Cover_Circle.c
	$(CC)  $(CFLAGS) $(CINC) -o $(OBJ_DIR)$(@F) ..\HARDWEAR\Cover_Circle.c


#================================================================
# Commands before make execution
#================================================================
.PreMakeCommands:


#================================================================
# Commands after make execution
#================================================================
.PostMakeCommands:


#================================================================
# Clean
#================================================================
clean:
	del .\$(PROJECT)
	del $(OBJ_DIR)*$(OBJ_EXT)


