-- ----------------------------------------------------------
-- MDB Tools - A library for reading MS Access database files
-- Copyright (C) 2000-2011 Brian Bruns and others.
-- Files in libmdb are licensed under LGPL and the utilities under
-- the GPL, see COPYING.LIB and COPYING files respectively.
-- Check out http://mdbtools.sourceforge.net
-- ----------------------------------------------------------

-- That file uses encoding UTF-8

CREATE TABLE `AspectText`
 (
	`TextType`			varchar, 
	`Planet1`			varchar, 
	`Planet2`			varchar, 
	`Planet1num`			INTEGER, 
	`Planet2num`			INTEGER, 
	`Aspect`			varchar, 
	`Aspectnum`			INTEGER, 
	`Text`			TEXT, 
	`Lang`			varchar
);

CREATE TABLE `biorythms`
 (
	`Name`			varchar, 
	`BirthDate`			DateTime
);

CREATE TABLE `births`
 (
	`name`			varchar, 
	`birthdate`			DateTime, 
	`hours`			INTEGER, 
	`minutes`			INTEGER, 
	`AMPM`			INTEGER, 
	`country`			varchar, 
	`state`			varchar, 
	`location`			varchar, 
	`longitude`			varchar, 
	`latitude`			varchar, 
	`timezone`			INTEGER, 
	`specialcode`			INTEGER, 
	`houroff`			INTEGER, 
	`minoff`			INTEGER, 
	`rect`			INTEGER, 
	`sex`			INTEGER
);

CREATE TABLE `FileList`
 (
	`name`			varchar, 
	`comments`			varchar, 
	`filename`			varchar, 
	`filenum`			INTEGER, 
	`IsTextReport`			INTEGER, 
	`FileType`			INTEGER, 
	`counter`			INTEGER, 
	`has_cover`			INTEGER, 
	`has_comments`			INTEGER, 
	`ListType`			varchar, 
	`Folder`			INTEGER
);

CREATE TABLE `Folders`
 (
	`folder_num`			INTEGER, 
	`folder_name`			varchar
);

CREATE TABLE `HelpText`
 (
	`texttype`			varchar, 
	`Text`			TEXT, 
	`iChunk`			INTEGER, 
	`Lang`			varchar
);

CREATE TABLE `locations`
 (
	`country`			varchar, 
	`state`			varchar, 
	`location`			varchar, 
	`longitude`			varchar, 
	`latitude`			varchar, 
	`timezone`			INTEGER, 
	`specialcode`			INTEGER, 
	`houroff`			INTEGER, 
	`minoff`			INTEGER, 
	`state_cd`			varchar, 
	`state_fips`			varchar, 
	`place_fips`			varchar
);

CREATE TABLE `numerology`
 (
	`ListName`			varchar, 
	`BirthDate`			DateTime, 
	`BirthFirst`			varchar, 
	`BirthMiddle`			varchar, 
	`BirthLast`			varchar, 
	`BirthInclude`			INTEGER, 
	`CurrentFirst`			varchar, 
	`CurrentLast`			varchar, 
	`CurrentMiddle`			varchar, 
	`Opt1First`			varchar, 
	`Opt1Middle`			varchar, 
	`Opt1Last`			varchar, 
	`CurrentInclude`			INTEGER, 
	`Opt1Include`			INTEGER, 
	`Opt2First`			varchar, 
	`Opt2Middle`			varchar, 
	`Opt2Last`			varchar, 
	`Opt2Include`			INTEGER, 
	`Counter`			INTEGER
);

CREATE TABLE `rectification`
 (
	`name`			varchar, 
	`birthdate`			DateTime, 
	`birth_time_known`			INTEGER, 
	`rect_system`			INTEGER, 
	`hours`			INTEGER, 
	`minutes`			INTEGER, 
	`am_pm`			INTEGER, 
	`angle`			INTEGER, 
	`sign`			INTEGER, 
	`totalminutes`			INTEGER, 
	`degree`			varchar
);

CREATE TABLE `RegularText`
 (
	`TextType`			varchar, 
	`Key1`			varchar, 
	`key2`			varchar, 
	`Key1num`			INTEGER, 
	`Key2num`			INTEGER, 
	`Text`			TEXT, 
	`Lang`			varchar
);

CREATE TABLE `relocations`
 (
	`country`			varchar, 
	`state`			varchar, 
	`location`			varchar, 
	`longitude`			varchar, 
	`latitude`			varchar, 
	`timezone`			INTEGER, 
	`specialcode`			INTEGER, 
	`houroff`			INTEGER, 
	`minoff`			INTEGER, 
	`name`			varchar, 
	`birthdate`			DateTime, 
	`personal`			varchar
);

CREATE TABLE `ReportText`
 (
	`texttype`			varchar, 
	`textkey`			varchar, 
	`iIndex`			INTEGER, 
	`iTextKey`			INTEGER, 
	`text`			TEXT, 
	`Lang`			varchar
);

CREATE TABLE `transits`
 (
	`name`			varchar, 
	`birthdate`			DateTime, 
	`hours`			INTEGER, 
	`minutes`			INTEGER, 
	`AMPM`			INTEGER, 
	`country`			varchar, 
	`state`			varchar, 
	`location`			varchar, 
	`longitude`			varchar, 
	`latitude`			varchar, 
	`timezone`			INTEGER, 
	`specialcode`			INTEGER, 
	`houroff`			INTEGER, 
	`minoff`			INTEGER, 
	`event`			varchar, 
	`transdate`			DateTime
);

CREATE TABLE `zip_code_latlong`
 (
	`zip_code`			varchar, 
	`longitude`			varchar, 
	`latitude`			varchar
);


