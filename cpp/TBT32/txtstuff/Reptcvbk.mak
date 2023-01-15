
# Convert REPORTS Back to .AST

.SUFFIXES: .AST $(EXT)

all:  $(DST)\gender.AST $(DST)\chhead.AST $(DST)\RETURN.AST \
      $(DST)\STRING.AST $(DST)\monthstr.AST $(DST)\ARABIC.AST \
      $(DST)\helio.AST $(DST)\PROBLEM.AST $(DST)\FIXEDST.AST \
      $(DST)\NUMERIC.AST $(DST)\PROGRESS.AST $(DST)\TRANSITR.AST \
      $(DST)\TRANSAFT.AST $(DST)\COMPOS.AST $(DST)\COMPAT.AST \
      $(DST)\COSUMMR.AST $(DST)\NATAL.AST $(DST)\SUMMARY.AST \
      $(DST)\PROBRES.AST $(DST)\ARABNAM.AST $(DST)\FIXDNAMS.AST \
      $(DST)\COTRANS.AST

$(DST)\gender.AST :  $(SRC)\gender$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\chhead.AST :  $(SRC)\chhead$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\RETURN.AST :  $(SRC)\RETURN$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\STRING.AST :  $(SRC)\STRING$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\monthstr.AST :  $(SRC)\monthstr$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\ARABIC.AST :  $(SRC)\ARABIC$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\helio.AST :  $(SRC)\helio$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\PROBLEM.AST : $(SRC)\PROBLEM$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\PROBRES.AST : $(SRC)\PROBRES$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\FIXEDST.AST : $(SRC)\FIXEDST$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\NUMERIC.AST : $(SRC)\NUMERIC$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\PROGRESS.AST : $(SRC)\PROGRESS$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\TRANSITR.AST : $(SRC)\TRANSITR$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\TRANSAFT.AST : $(SRC)\TRANSAFT$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\COMPOS.AST : $(SRC)\COMPOS$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\COMPAT.AST : $(SRC)\COMPAT$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\COSUMMR.AST : $(SRC)\COSUMMR$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\NATAL.AST : $(SRC)\NATAL$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\SUMMARY.AST : $(SRC)\SUMMARY$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\ARABNAM.AST : $(SRC)\ARABNAM$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\FIXDNAMS.AST : $(SRC)\FIXDNAMS$(EXT)
  $(FMT)TOAST $*$(EXT) $@

$(DST)\COTRANS.AST : $(DST)\COTRANS$(EXT)
  $(FMT)TOAST $*$(EXT) $@
