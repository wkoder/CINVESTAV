use strict;

die 'Arg: precission' if @ARGV != 1;

sub acos { atan2( sqrt(1 - $_[0] * $_[0]), $_[0] ) }

my $PI = acos(-1);
my $precission = $ARGV[0];
my $delta = 0.1;
while ($precission > 0) {
	$precission--;
	$delta /= 10;
}

my $terms = 1;
my $approx = 4;
my $denom = 1;
my $i = 0;
while (abs($PI - $approx) > $delta) {
	$denom += 2;
	$terms++;
	
	my $val = 4 / $denom;
	if ($terms % 2 == 0) {
		$val = -$val;
	}
	
	$approx += $val;
}

print "$approx $terms\n";
