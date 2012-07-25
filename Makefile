##################################################
#    makefile for versitile password generator   #
##################################################

LIBNAME = VPwdGen

FILES = Globals PwdOpts \
	Characters Koremutakes DiceWords SkeyWords \
	Seeder MtRand PwdGen

PROGRAMS = vpwd-gen #test-rand

VERSION   = 0.1
USE_CLANG = 1
IS_64BIT  = 1
#HAS_LIBCURL  = 1

include makefiles/Makefile.common
