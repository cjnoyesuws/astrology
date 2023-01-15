path %PATH%;"c:\program files\winzip self-extractor";"C:\Program Files\Winzip"

echo %PATH%

SET VER=229

wzzip /a c:\newversionstaging\zips\ASTRW%VER%.zip h:\Astrow32dev\installs\shareware\ASTRW%VER%.exe
copy h:\Astrow32dev\installs\shareware\ASTRW%VER%.exe c:\newversionstaging\zips\

wzzip /a c:\newversionstaging\zips\ASTRWDX%VER%.zip h:\Astrow32dev\installs\astrodeluxedemo\astrosetup.exe
copy h:\Astrow32dev\installs\astrodeluxedemo\astrosetup.exe c:\newversionstaging\zips\ASTRWDX%VER%.exe

wzzip /a c:\newversionstaging\zips\ASTRWPR%VER%.zip h:\Astrow32dev\installs\astrodeluxedemo\astrosetup.exe
copy h:\Astrow32dev\installs\astrodeluxedemo\astrosetup.exe c:\newversionstaging\zips\ASTRPR%VER%.exe

wzzip /a c:\newversionstaging\zips\ASTRWDX%VER%FULL.zip h:\Astrow32dev\installs\astrodeluxedemo\astrosetup.exe
wzzip /a c:\newversionstaging\zips\ASTRWDX%VER%FULL.zip h:\Astrow32dev\installs\calculators\calculators.exe
wzzip /a c:\newversionstaging\zips\ASTRWDX%VER%FULL.zip h:\Astrow32dev\installs\tbt32\tbt32setup.exe
wzzip /a c:\newversionstaging\zips\ASTRWDX%VER%FULL.zip h:\Astrow32dev\installs\viewers\viewers.exe
wzzip /a c:\newversionstaging\zips\ASTRWDX%VER%FULL.zip h:\Astrow32dev\installs\expertimporter\expertimport.exe
wzzip /a c:\newversionstaging\zips\ASTRWDX%VER%FULL.zip c:\newversionstaging\deluxedemo\setup.exe
wzzip /a c:\newversionstaging\zips\ASTRWDX%VER%FULL.zip c:\newversionstaging\deluxedemo\autorun.inf
wzzip /a c:\newversionstaging\zips\ASTRWDX%VER%FULL.zip c:\newversionstaging\deluxedemo\astromanual.pdf
wzipse32 c:\newversionstaging\zips\ASTRWDX%VER%FULL.zip -setup -t h:\astrow32dev\installs\dialog.wz -mokcancel h:\astrow32dev\installs\message.wz -c ./setup.exe


wzzip /a c:\newversionstaging\zips\ASTRWPR%VER%FULL.zip h:\Astrow32dev\installs\astroprodemo\astrosetup.exe
wzzip /a c:\newversionstaging\zips\ASTRWPR%VER%FULL.zip h:\Astrow32dev\installs\calculators\calculators.exe
wzzip /a c:\newversionstaging\zips\ASTRWPR%VER%FULL.zip h:\Astrow32dev\installs\tbt32\tbt32setup.exe
wzzip /a c:\newversionstaging\zips\ASTRWPR%VER%FULL.zip h:\Astrow32dev\installs\viewers\viewers.exe
wzzip /a c:\newversionstaging\zips\ASTRWPR%VER%FULL.zip h:\Astrow32dev\installs\expertimporter\expertimport.exe
wzzip /a c:\newversionstaging\zips\ASTRWPR%VER%FULL.zip h:\newversionstaging\deluxedemo\setup.exe
wzzip /a c:\newversionstaging\zips\ASTRWPR%VER%FULL.zip h:\newversionstaging\deluxedemo\autorun.inf
wzzip /a c:\newversionstaging\zips\ASTRWPR%VER%FULL.zip h:\newversionstaging\prodemo\astromanual.pdf
wzipse32 c:\newversionstaging\zips\ASTRWPR%VER%FULL.zip -setup -t h:\astrow32dev\installs\dialog.wz -mokcancel h:\astrow32dev\installs\message.wz -c ./setup.exe