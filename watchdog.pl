#!/usr/bin/perl -wT






$path = $ENV{'PATH'};       # $path now tainted

$ENV{'PATH'} = '/bin:/usr/bin';
delete @ENV{'IFS', 'CDPATH', 'ENV', 'BASH_ENV'};

$path = $ENV{'PATH'};



$stayup=1;
while($stayup){
    system("/misc/home/visi/lalondma/junk/TechVisionCoproc/src/TechVisionCoproc");
    if($?==0){
	$stayup=0;
    }
    elsif ($? == -1) {
    print "failed to execute: $!\n";
    }
    elsif ($? & 127) {
    printf "child died with signal %d, %s coredump\n",
    ($? & 127), ($? & 128) ? 'with' : 'without';
    }
    else {
    printf "child exited with value %d\n", $? >> 8;
    }

} 
   system("mkdir /root/y");
