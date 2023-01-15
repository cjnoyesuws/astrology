# make file for text

.SUFFIXES : .NDX $(EXT) .TXT .SYM .BSM


#if XTXT=YES
XTXTNM=$(DST)\comptasp.ndx $(DST)\midptsin.ndx
#else
XTXTNM=
#endif


all : STRTABLE.BSM TEXT.BSM $(DST)\planets.ndx $(DST)\sighouse.ndx \
	  $(DST)\houses.ndx $(DST)\aspects.ndx \
	  $(DST)\summary.ndx $(DST)\compahse.ndx \
	  $(DST)\transhse.ndx $(DST)\transasp.ndx \
	  $(DST)\compasum.ndx $(DST)\prograsp.ndx $(XTXTNM)

TEXT.BSM : TEXT.SYM
  MKBSR TEXT.BSM TEXT.SYM

STRTABLE.BSM : STRING.TAB CHAR.TAB
    MKSTRB STRING.TAB CHAR.TAB

# planet

$(DST)\planets.ndx : $(SRC)\as1text$(EXT) $(SRC)\as10text$(EXT)
   +copy $(DST)\planets.TXT $(DST)\planets.TX$
   +del $(DST)\planets.TXT
   +copy $(DST)\planets.NDX $(DST)\planets.ND$
   +del $(DST)\planets.NDX
   buildtxt $(SRC)\as1text$(EXT) $(DST)\planets $(FMT) T
   buildtxt $(SRC)\as10text$(EXT) $(DST)\planets $(FMT) T
   buildtxt $(SRC)\as12text$(EXT) $(DST)\planets $(FMT) T

# signs in houses

$(DST)\sighouse.ndx : $(SRC)\as11text$(EXT)
   +copy $(DST)\sighouse.TXT $(DST)\sighouse.TX$
   +del $(DST)\sighouse.TXT
   +copy $(DST)\sighouse.NDX $(DST)\sighouse.ND$
   +del $(DST)\sighouse.NDX
   buildtxt $(SRC)\as11text$(EXT) $(DST)\sighouse $(FMT) T

# houses

$(DST)\houses.ndx : $(SRC)\as2text$(EXT)
   +copy $(DST)\houses.TXT $(DST)\houses.TX$
   +del $(DST)\houses.TXT
   +copy $(DST)\houses.NDX $(DST)\houses.ND$
   +del $(DST)\houses.NDX
   buildtxt $(SRC)\as2text$(EXT) $(DST)\houses $(FMT) T


# aspects

$(DST)\aspects.ndx : $(SRC)\as3atext$(EXT) $(SRC)\as3ctext$(EXT)
   +copy $(DST)\aspects.TXT $(DST)\aspects.TX$
   +del $(DST)\aspects.TXT
   +copy $(DST)\aspects.NDX $(DST)\aspects.ND$
   +del $(DST)\aspects.NDX
   3dbldtxt $(SRC)\as3atext$(EXT) $(DST)\aspects $(FMT) T
   3dbldtxt $(SRC)\as3ctext$(EXT) $(DST)\aspects $(FMT) T

# summary

$(DST)\summary.ndx : $(SRC)\as3btext$(EXT)
   +copy $(DST)\summary.TXT $(DST)\summary.TX$
   +del $(DST)\summary.TXT
   +copy $(DST)\summary.NDX $(DST)\summary.ND$
   +del $(DST)\summary.NDX
   buildtxt $(SRC)\as3btext$(EXT) $(DST)\summary $(FMT) T

# compat houses

$(DST)\compahse.ndx : $(SRC)\as5text$(EXT)
   +copy $(DST)\compahse.TXT $(DST)\compahse.TX$
   +del $(DST)\compahse.TXT
   +copy $(DST)\compahse.NDX $(DST)\compahse.ND$
   +del $(DST)\compahse.NDX
   buildtxt $(SRC)\as5text$(EXT) $(DST)\compahse $(FMT) T

# compat summary

$(DST)\compasum.ndx : $(SRC)\as6text$(EXT) $(SRC)\as13text$(EXT)
   +copy $(DST)\compasum.TXT $(DST)\compasum.TX$
   +del $(DST)\compasum.TXT
   +copy $(DST)\compasum.NDX $(DST)\compasum.ND$
   +del $(DST)\compasum.NDX
   buildtxt $(SRC)\as6text$(EXT) $(DST)\compasum $(FMT) T
   buildtxt $(SRC)\as13text$(EXT) $(DST)\compasum $(FMT) T

# transits general

$(DST)\transhse.ndx : $(SRC)\as7text$(EXT) $(SRC)\as9text$(EXT)
   +copy $(DST)\transhse.TXT $(DST)\transhse.TX$
   +del $(DST)\transhse.TXT
   +copy $(DST)\transhse.NDX $(DST)\transhse.ND$
   +del $(DST)\transhse.NDX
   buildtxt $(SRC)\as7text$(EXT) $(DST)\transhse $(FMT) T
   buildtxt $(SRC)\as9text$(EXT) $(DST)\transhse $(FMT) T

# transits aspects

$(DST)\transasp.ndx : $(SRC)\as8text$(EXT)
   +copy $(DST)\transasp.TXT $(DST)\transasp.TX$
   +del $(DST)\transasp.TXT
   +copy $(DST)\transasp.NDX $(DST)\transasp.ND$
   +del transasp.NDX
   3dbldtxt $(SRC)\as8text$(EXT) $(DST)\transasp $(FMT) T

# Progressions Aspects

$(DST)\prograsp.ndx : $(SRC)\as14text$(EXT) $(SRC)\as15text$(EXT)
   +copy $(DST)\prograsp.TXT $(DST)\prograsp.TX$
   +del $(DST)\prograsp.TXT
   +copy $(DST)\prograsp.NDX $(DST)\prograsp.ND$
   +del $(DST)\prograsp.NDX
   3dbldtxt $(SRC)\as14text$(EXT) $(DST)\prograsp $(FMT) T
   3dbldtxt $(SRC)\as15text$(EXT) $(DST)\prograsp $(FMT) T

#if XTXT=YES

$(DST)\comptasp.ndx : $(SRC)\as16text$(EXT) $(SRC)\as17text$(EXT)
   +copy $(DST)\comptasp.TXT $(DST)\comptasp.TX$
   +del $(DST)\comptasp.TXT
   +copy $(DST)\comptasp.NDX $(DST)\comptasp.ND$
   +del $(DST)\comptasp.NDX
   3dbldtxt $(SRC)\as16text$(EXT) $(DST)\comptasp $(FMT) T
   3dbldtxt $(SRC)\as17text$(EXT) $(DST)\comptasp $(FMT) T


$(DST)\midptsin.ndx : $(SRC)\as18text$(EXT) $(SRC)\as19text$(EXT)
   +copy $(DST)\midptsin.TXT $(DST)\midptsin.TX$
   +del $(DST)\midptsin.TXT
   +copy $(DST)\midptsin.NDX $(DST)\midptsin.ND$
   +del $(DST)\midptsin.NDX
   3dbldtxt $(SRC)\as18text$(EXT) $(DST)\midptsin $(FMT) T
   3dbldtxt $(SRC)\as19text$(EXT) $(DST)\midptsin $(FMT) T

#endif


