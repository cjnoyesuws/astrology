<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML><HEAD>
<META http-equiv=Content-Type content="text/html; charset=windows-1252"></HEAD>
<BODY><PRE>#!/usr/bin/perl5
#CHANGE THE ABOVE SETTING TO WHERE PERL5 IS ON YOUR COMPUTER
#usually /usr/local/bin/perl.

#CHANGE THIS TO THE DIRECTORY WHERE YOUR WEB SPACE IS
$filepath = "/home/boutell/html";

#CHANGE THIS TO THE FILE CONTAINING YOUR SEARCH INDEX,
#created with search-index, WHICH MUST BE RUN **OFTEN**
$indexFile = "searchindex.txt";

use CGI;
$query = new CGI;

chdir($filepath);

$target = $query-&gt;param('target');
if ($target eq "") {
	&amp;header;
	&amp;form;
	&amp;footer;
	exit 0;
}
$rule = $query-&gt;param('rule');

# Simple HTML flusher
$target =~ s/\&lt;.*?\&gt;//g;
# Case insensitive
$target =~ tr/A-Z/a-z/;
# If it's not a letter, it's whitespace
$target =~ s/[^a-z]/ /g;

@words = split(/ /, $target);
if (open(IN, $indexFile)) {
	while ($line = &lt;IN&gt;) {
		my($wordCount, $score);
		if ($line =~ /^(\S+) /) {
			$filename = $1;
		} else {
			next;
		}
		for $w (@words) {
			if ($line =~ /(\d+):$w/)
			{ 
				$score += $1;
				$wordCount ++;
			}
		}
		if ($rule eq "and") {
			if ($wordCount == int(@words)) {
				push @files, "$score:$filename";
			}	
		} elsif ($wordCount &gt; 0) {
			push @files, "$score:$filename";
		}
	}
}

&amp;header;
if (!int(@files)) {
	print "&lt;h3&gt;Sorry, no pages were found.\n&lt;/h3&gt;\n";
} else {
	print "&lt;h3&gt;The following pages were found:&lt;/h3&gt;\n";
}
print "&lt;ul&gt;\n";

@files = sort {$b &lt;=&gt; $a} @files;

for $n (@files) {
	my($score, $file) = split(/:/, $n);
# Skip forbidden pages. These examples work well for our site.
#	if ($file =~ /\/usage/) {
#		next;
#	}
#	if ($file =~ /\/wusage\/example/) {
#		next;
#	}
	$title = "";
	$data = "";
	if (open(IN, "$filepath$file")) {
		while ($line = &lt;IN&gt;) {
			$data .= $line;
			if ($data =~ /&lt;title&gt;\s*(.*)\s*\&lt;\/title&gt;/i) {
				$title = $1;
				last;
			}
		} 
		close(IN);
	}
	if ($title eq "") {
		$title = "$file";
	}
	print "&lt;li&gt;$score: &lt;a href=\"$file\"&gt;$title&lt;\/a&gt;\n";
}
print "&lt;/ul&gt;\n";
print "&lt;hr&gt;\n";
&amp;form;
&amp;footer;

sub header
{
	print "Content-type: text/html\n\n";
	&amp;template("before-head");
	print "&lt;title&gt;Search Boutell.Com&lt;/title&gt;\n";
	&amp;template("after-head");
	&amp;template("before-body");
	print "&lt;h1&gt;Search Boutell.Com&lt;/h1&gt;\n";
}

sub footer
{
	&amp;template("after-body");
}

sub template
{
        my($file) = @_;
        open(IN, "/home/admin/html/$file");
        while ($line = &lt;IN&gt;) {
                print $line;
        }
        close(IN);
}

sub form
{
	print &lt;&lt;EOM
Enter one or more words to look for.
&lt;p&gt;
&lt;strong&gt;For privacy reasons, this program
DOES NOT SEARCH THE WORLD BIRTHDAY WEB.&lt;/strong&gt;
&lt;p&gt;
&lt;form action="/search.cgi" method="GET"&gt;
Return pages containing
&lt;select name="rule"&gt;
&lt;option value="and"&gt;ALL
&lt;option value="any"&gt;ANY
&lt;/select&gt;
of these words: 
&lt;input name="target"&gt;
&lt;input type="submit" value="Go!"&gt;
&lt;/form&gt;
&lt;p&gt;
&lt;a href="/search/"&gt;&lt;em&gt;FREE:&lt;/em&gt; You can have this search facility
on your own site!&lt;/a&gt;
EOM
;
}


</PRE></BODY></HTML>
