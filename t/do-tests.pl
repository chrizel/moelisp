#!/usr/bin/perl

use warnings;
use strict;
use Term::ANSIColor;

my $test_name_width = 16;

sub print_test_row {
    my ($test_name, $right, $num) = @_;
    my $dots = '.' x ($test_name_width - length $test_name);
    my $s = $num > 1 ? 's' : '';
    my $tests = sprintf '%3d %-5s ', $num, "test$s";
    print $test_name . $dots . $tests;
}

my @tests = glob "./t/????-*.lisp";
my $wrong_sum = 0;
my $sum = 0;

foreach my $test (@tests) {
    my $out = `./moe ./t/testlib.lisp $test`;
    my ($name) = ($test =~ /^.*\/(\d+-.+)\.lisp$/);

    my $right = 0;
    my $num = 0;
    my @wrong = ();

    if ($name eq "0000-test") {
        $num = length $out;
        if ($out eq "-!!---!!!-!") {
            $right = $num;
        } else {
            $right = 0;
            @wrong = (0..$num);
        }
    } else {
        foreach my $c (split //, $out) {
            if ($c eq "-") {
                ++$right;
            } else {
                push @wrong, ($num);
            }
            ++$num;
        }
    }

    print_test_row $name, $right, $num;
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
    $sum += $num;
}

print "---\n";
if ($wrong_sum > 0) {
    my $s = $wrong_sum > 1 ? 's' : '';
    print color 'red';
    print "$wrong_sum false test$s detected.\n";
    print color 'reset';
} else {
    print color 'green';
    print "All $sum tests are ok.\n";
    print color 'reset';
}
