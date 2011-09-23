#!/usr/bin/perl -w

 ###################################################################################
#                                                                                   #
#  Copyright 2010 Cedric Priscal                                                    ##
#                                                                                   ##
#  This file is part of Octopus Development Kit.                                    ##
#                                                                                   ##
#  Octopus Development Kit is free software: you can redistribute it and/or         ##
#  modify it under the terms of the GNU General Public License as                   ##
#  published by the Free Software Foundation, either version 3 of the               ##
#  License, or (at your option) any later version.                                  ##
#                                                                                   ##
#  Octopus Development Kit is distributed in the hope that it will be useful,       ##
#  but WITHOUT ANY WARRANTY; without even the implied warranty of                   ##
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    ##
#  GNU General Public License for more details.                                     ##
#                                                                                   ##
#  You should have received a copy of the GNU General Public License                ##
#  along with Octopus Development Kit. If not, see <http://www.gnu.org/licenses/>.  ##
#                                                                                   ##
######################################################################################
 ####################################################################################

use strict;
use warnings;
use File::Copy;
use File::Basename;

sub get_virtual_directory($$$);
sub copy_search_replace($$$$);
sub create_project($);
sub update_project($);
sub help();

my ($cmd, $project) = @ARGV;

if (!defined($cmd) || !defined($project)) {
    help();
    exit 1;
}

if ($cmd eq "create") {
    create_project($project);
} elsif ($cmd eq "update") {
    update_project($project);
} else {
    print "Unkown command: $cmd\n";
    help();
    exit 1;
}

# Done
exit 0;

sub help() {
    print "Usage: octopusdk.pl <create|update> <project>\n";
    print "\n";
    print "This script creates a new project based on the HelloWorld project,\n";
    print "or updates an existing project with all libraries.\n";
    print "\n";
    print "./octopusdk.pl create MyRobot\n";
    print "  Create a new project named MyRobot.project in \"robots\" directory.\n";
    print "\n";
    print "./octopusdk.pl update MyRobot\n";
    print "  Update the existing project MyRobot by adding all source files found in libs/avr and libs/common.\n";
    print "\n";
    print "Copyright 2011 Cedric Priscal, \n";
    print "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n";
    print "This is free software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law.\n";
}

sub get_virtual_directory($$$) {
    my ($header, $dir, $ext) = @_;
    my $out = '';

    # get list of files/subdirs
    my @files = glob($dir.'/*');
    foreach my $file (@files) {
        if ($file =~ /$ext/) {
            $out .= $header."<File Name=\"../../$file\"/>\n";
        } else {
            # maybe a directory
            my $a = get_virtual_directory($header.'  ', $file, $ext);
            if ($a) {
                my $name = basename($file);
                $out .= $header."<VirtualDirectory Name=\"$name\">\n";
                $out .= $a;
                $out .= $header."</VirtualDirectory>\n";
            }
        }
    }

    return $out;
}

sub copy_search_replace($$$$) {
    my ($from, $to, $search, $replace) = @_;
    my $fh;

    # Read $from
    open($fh, '<', $from);
    binmode($fh);
    my $size = (stat($fh))[7];
    my $fcontent;
    read $fh, $fcontent, $size;
    close($fh);

    # Search and replace
    $fcontent =~ s/$search/$replace/sg;

    # Write $to
    open($fh, '>', $to);
    binmode($fh);
    print $fh $fcontent;
    close($fh);
}

sub create_project($) {
    my $name = shift;

    # Create project directory
    mkdir "robots/$name";

    # Add source file
    copy_search_replace(
        "robots/Template/Template.cpp",
        "robots/$name/$name.cpp",
        'Template',
        $name
    );

    copy_search_replace(
        "robots/Template/Template.project",
        "robots/$name/$name.project",
        'CodeLite_Project Name="Template"',
        'CodeLite_Project Name="'.$name.'"'
    );

    print "Project \"$name\" created in \"robots/$name/$name.project\"\n";

    # Update list of source and header files in the project
    update_project($name);
}

sub update_project($) {
    my $name = shift;

    # Get complete list of source files, with all modules
    my $xmldirs =
        "  <VirtualDirectory Name=\"src\">\n".
        "    <VirtualDirectory Name=\"libs\">\n".
        "      <VirtualDirectory Name=\"avr\">\n".
        get_virtual_directory("        ", "libs/avr", '\.cpp$').
        "      </VirtualDirectory>\n".
        "      <VirtualDirectory Name=\"common\">\n".
        get_virtual_directory("        ", "libs/common", '\.cpp$').
        "      </VirtualDirectory>\n".
        "      <VirtualDirectory Name=\"sensors\">\n".
        get_virtual_directory("        ", "libs/sensors", '\.cpp$').
        "      </VirtualDirectory>\n".
        "    </VirtualDirectory>\n".
        "    <VirtualDirectory Name=\"robots\">\n".
        "      <VirtualDirectory Name=\"$name\">\n".
        get_virtual_directory("        ", "robots/$name", '\.cpp$').
        "      </VirtualDirectory>\n".
        "    </VirtualDirectory>\n".
        "  </VirtualDirectory>\n".
        "  <VirtualDirectory Name=\"include\">\n".
        "    <VirtualDirectory Name=\"libs\">\n".
        "      <VirtualDirectory Name=\"avr\">\n".
        get_virtual_directory("        ", "libs/avr", '\.h$').
        "      </VirtualDirectory>\n".
        "      <VirtualDirectory Name=\"common\">\n".
        get_virtual_directory("        ", "libs/common", '\.h$').
        "      </VirtualDirectory>\n".
        "      <VirtualDirectory Name=\"sensors\">\n".
        get_virtual_directory("        ", "libs/sensors", '\.h$').
        "      </VirtualDirectory>\n".
        "    </VirtualDirectory>\n".
        "    <VirtualDirectory Name=\"robots\">\n".
        "      <VirtualDirectory Name=\"$name\">\n".
        get_virtual_directory("        ", "robots/$name", '\.h$').
        "      </VirtualDirectory>\n".
        "    </VirtualDirectory>\n".
        "  </VirtualDirectory>\n";

    copy_search_replace(
        "robots/$name/$name.project",
        "robots/$name/$name.project",
        '  <VirtualDirectory.*<\/VirtualDirectory>\n',
        $xmldirs
    );

    print "Project \"$name\" updated with all libraries.\n";
}
