
# COPY REPORTS To Destination Directory

.SUFFIXES: .TBL

all: $(DST)\GLOBAL.TBL $(DST)\helio.TBL \
	$(DST)\RETURN.TBL $(DST)\FIXEDST.TBL $(DST)\ARABIC.TBL \
	$(DST)\NUMERIC.TBL $(DST)\PROGRESS.TBL $(DST)\TRANSITR.TBL \
	$(DST)\COMPOS.TBL $(DST)\COMPAT.TBL $(DST)\NATAL.TBL \
	$(DST)\SUMMARY.TBL $(DST)\COSUMMR.TBL $(DST)\COTRANS.TBL \
	$(DST)\PROBLEM.TBL

$(DST)\GLOBAL.TBL: $(SRC)\GLOBAL.TBL
	+COPY $(SRC)\GLOBAL.TBL $(DST)\GLOBAL.TBL

$(DST)\helio.TBL: $(SRC)\helio.TBL
	+COPY $(SRC)\HELIO.TBL $(DST)\HELIO.TBL

$(DST)\PROBLEM.TBL: $(SRC)\PROBLEM.TBL
	+COPY $(SRC)\PROBLEM.TBL $(DST)\PROBLEM.TBL

$(DST)\RETURN.TBL: $(SRC)\RETURN.TBL
	+COPY $(SRC)\RETURN.TBL $(DST)\RETURN.TBL

$(DST)\FIXEDST.TBL: $(SRC)\FIXEDST.TBL
	+COPY $(SRC)\FIXEDST.TBL $(DST)\FIXEDST.TBL

$(DST)\ARABIC.TBL: $(SRC)\ARABIC.TBL
	+COPY $(SRC)\ARABIC.TBL $(DST)\ARABIC.TBL


$(DST)\NUMERIC.TBL: $(SRC)\NUMERIC.TBL
	+COPY $(SRC)\NUMERIC.TBL $(DST)\NUMERIC.TBL

$(DST)\PROGRESS.TBL: $(SRC)\PROGRESS.TBL
	+COPY $(SRC)\PROGRESS.TBL $(DST)\PROGRESS.TBL

$(DST)\TRANSITR.TBL: $(SRC)\TRANSITR.TBL
	+COPY $(SRC)\TRANSITR.TBL $(DST)\TRANSITR.TBL

$(DST)\COMPOS.TBL: $(SRC)\COMPOS.TBL
	+COPY $(SRC)\COMPOS.TBL $(DST)\COMPOS.TBL

$(DST)\COMPAT.TBL: $(SRC)\COMPAT.TBL
	+COPY $(SRC)\COMPAT.TBL $(DST)\COMPAT.TBL

$(DST)\COSUMMR.TBL: $(SRC)\COSUMMR.TBL
	+COPY $(SRC)\COSUMMR.TBL $(DST)\COSUMMR.TBL

$(DST)\NATAL.TBL: $(SRC)\NATAL.TBL
	+COPY $(SRC)\NATAL.TBL $(DST)\NATAL.TBL

$(DST)\SUMMARY.TBL: $(SRC)\SUMMARY.TBL
	+COPY $(SRC)\SUMMARY.TBL $(DST)\SUMMARY.TBL

$(DST)\COTRANS.TBL: $(SRC)\COTRANS.TBL
	+COPY $(SRC)\COTRANS.TBL $(DST)\COTRANS.TBL

