#!/usr/bin/perl

# Usage genconf.pl conf.skel
# conf.skel shall be formated for sprintf
@x=<>;
$fmt=join("",@x);
print $fmt;
for( $i=16; $i ;$i-- ){
      for( $j=16; $j ;$j-- ){
         my $house=chr(65+16-$i);
         my $unit=16-$j;
         printf($fmt,$house,$unit,"$house$unit");
         }}

# printf($fmt,"A","B","C");
# printf($fmt,"xA","B","C");
