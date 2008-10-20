#!/usr/bin/perl

use warnings;
use strict;
use Term::ANSIColor;

my @tests = glob "./t/????-*.lisp";
my $wrong_sum = 0;

foreach my $test (@tests) {
    my $out = `./moe ./t/testlib.lisp $test`;
    my ($name) = ($test =~ /^.*\/(\d+-.+)\.lisp$/);

    my $right = 0;
    my $num = 0;
    my @wrong = ();

    foreach my $c (split //, $out) {
        if ($c eq "-") {
            ++$right;
        } else {
            push @wrong, ($num);
        }
        ++$num;
    }

    print "$name: ";
    if ($right == $num) {
        print color 'green';
        print "ok\n";
        print color 'reset';
    } else {
        my $wrong = @wrong;
        my $s = $wrong > 1 ? 's' : '';
        print color 'red';
        print "$wrong false test$s detected:\n";
        foreach my $w (@wrong) {
            print "   Test $w\n";
        }
        print color 'reset';

        $wrong_sum += @wrong;
    }
}

print "---\n";
if ($wrong_sum > 0) {
    my $s = $wrong_sum > 1 ? 's' : '';
    print color 'red';
    print "$wrong_sum false test$s detected.\n";
    print color 'reset';
} else {
    print color 'green';
    print "All tests are ok.\n";
    print color 'reset';
}
