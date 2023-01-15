# make file for text

.SUFFIXES : $(SRC)\.NDX .NDX .TXT


#if XTXT=YES
XTXTNM=$(DST)\comptasp.ndx $(DST)\midptsin.ndx
#else
XTXTNM=
#endif


all : $(DST)\planets.ndx $(DST)\sighouse.ndx \
	  $(DST)\houses.ndx $(DST)\aspects.ndx \
	  $(DST)\summary.ndx $(DST)\compahse.ndx \
	  $(DST)\transhse.ndx $(DST)\transasp.ndx \
	  $(DST)\compasum.ndx $(DST)\prograsp.ndx $(XTXTNM)

# planet

$(DST)\planets.ndx : $(SRC)\planets.NDX
   +COPY $(SRC)\planets.TXT $(DST)\planets.TXT
   +COPY $(SRC)\planets.NDX $(DST)\planets.NDX

# signs in houses

$(DST)\sighouse.ndx : $(SRC)\sighouse.NDX
   +COPY $(SRC)\sighouse.TXT $(DST)\sighouse.TXT
   +COPY $(SRC)\sighouse.NDX $(DST)\sighouse.NDX

# houses

$(DST)\houses.ndx : $(SRC)\houses.NDX
   +COPY $(SRC)\houses.TXT $(DST)\houses.TXT
   +COPY $(SRC)\houses.NDX $(DST)\houses.NDX

# aspects

$(DST)\aspects.ndx : $(SRC)\aspects.NDX
   +COPY $(SRC)\aspects.TXT $(DST)\aspects.TXT
   +COPY $(SRC)\aspects.NDX $(DST)\aspects.NDX

# summary

$(DST)\summary.ndx : $(SRC)\summary.NDX
   +COPY $(SRC)\summary.TXT $(DST)\summary.TXT
   +COPY $(SRC)\summary.NDX $(DST)\summary.NDX

# compat houses

$(DST)\compahse.ndx : $(SRC)\compahse.NDX
   +COPY $(SRC)\compahse.TXT $(DST)\compahse.TXT
   +COPY $(SRC)\compahse.NDX $(DST)\compahse.NDX

# compat summary

$(DST)\compasum.ndx : $(SRC)\compasum.NDX
   +COPY $(SRC)\compasum.TXT $(DST)\compasum.TXT
   +COPY $(SRC)\compasum.NDX $(DST)\compasum.NDX

# transits general

$(DST)\transhse.ndx : $(SRC)\transhse.NDX
   +copy $(SRC)\transhse.TXT $(DST)\transhse.TXT
   +copy $(SRC)\transhse.NDX $(DST)\transhse.NDX

# transits aspects

$(DST)\transasp.ndx : $(SRC)\transasp.NDX
   +copy $(SRC)\transasp.TXT transasp.TXT
   +copy $(SRC)\transasp.NDX transasp.NDX

# Progressions Aspects

$(DST)\prograsp.ndx : $(SRC)\prograsp.NDX
   +COPY $(SRC)\prograsp.TXT $(DST)\prograsp.TXT
   +COPY $(SRC)\prograsp.NDX $(DST)\prograsp.NDX

#if XTXT=YES

$(DST)\comptasp.ndx : $(SRC)\comptasp.NDX
   +COPY $(SRC)\comptasp.TXT $(DST)\comptasp.TXT
   +COPY $(SRC)\comptasp.NDX $(DST)\comptasp.NDX

$(DST)\midptsin.ndx : $(SRC)\midptsin.NDX
   +COPY $(SRC)\midptsin.TXT $(DST)\midptsin.TXT
   +COPY $(SRC)\midptsin.NDX $(DST)\midptsin.NDX

#endif


