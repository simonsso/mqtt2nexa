#!/usr/bin/perl

# Usage genconf.pl conf.skel
# conf.skel shall be formated for sprintf
@x=<>;
my $num=1;
print "# AUTOGENERATED DO NOT EDIT BEGIN\n";
$fmt=join("",@x);
for( $i=16; $i ;$i-- ){
      for( $j=16; $j ;$j-- ){
         my $house=chr(65+16-$i);
         my $unit=16-$j;
         printf($fmt,$num++,"$house$unit",$house,$unit);
         }}

print "# AUTOGENERATED DO NOT EDIT END\n";