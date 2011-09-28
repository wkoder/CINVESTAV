use strict;
use warnings;
use diagnostics;

my $N = 8;
my $found = 0;

sub calc_next($\@);
sub calc_next($\@) {
	my $p = shift;
	my $pos = shift;
	if ($p == 8) {
		$found++;
		for (my $i = 0; $i < $N; $i++) {
			for (my $j = 0; $j < $N; $j++) {
				if ($j > 0) {
					print " ";
				}
				
				if ($i == $$pos[$j]) {
					print "*";
				} else {
					print "-";
				}
			}
			print "\n";
		}
		print "\n";
		return;
	}
	
	for (my $k = 0; $k < 8; $k++) {
		my $ok = 1;
		for (my $i = 0; $i < $p; $i++) {
			$ok &= $k != $$pos[$i] && $p-$i != abs($$pos[$i] - $k);
		}
		if ($ok) {
			$$pos[$p] = $k;
			calc_next($p+1, @$pos);
		}
	}
}

my @pos;
calc_next(0, @pos);
print "$found\n";
