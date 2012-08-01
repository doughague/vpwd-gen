##################################################
#   makefile for versatile password generator    #
##################################################

########################
#   user sepecifics    #
########################
# comment-out the following line to use gcc
USE_CLANG = 1
# comment-out the following line for 32-bit archetecture
IS_64BIT  = 1

########################
# do not modify below  #
########################
# library name
LIBNAME = VPwdGen
# header & source files to compile
FILES = Globals PwdOpts Characters Koremutakes DiceWords SkeyWords \
	Seeder MtRand PwdGen
# binary executable programs
PROGRAMS = vpwd-gen
# version number
VERSION   = 0.1
# general rules
include makefiles/Makefile.common
