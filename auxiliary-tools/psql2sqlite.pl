#!/usr/bin/env perl
#

@file = <STDIN>;

foreach (@file) {
    s/'/''/g;
    push @no_comments, $_ if    not /^--/       and
                                not /^$/        and
                                not /^REVOKE/   and
                                not /^SELECT/   and
                                not /^CREATE/   and
                                not /^GRANT/    and
                                not /^ALTER/    and
                                not /^    ADD/;

    s/"//g;
    $workshops_workshop_format = $1 if /^COPY workshops_workshop \((.+)\)/;
    $workshops_application_format = $1 if /^COPY workshops_application \((.+)\)/;
    $applications_applicant_format = $1 if /^COPY applications_applicant \((.+)\)/;
}
print   "DROP TABLE IF EXISTS objects;\n".
        "CREATE TABLE objects (id INT, type INT);\n".
        "DROP TABLE IF EXISTS times;\n".
        "CREATE TABLE times (object INT, name VARCHAR(32), value INT);\n".
        "DROP TABLE IF EXISTS strings;\n".
        "CREATE TABLE strings (object INT, name VARCHAR(32), value TEXT);\n".
        "DROP TABLE IF EXISTS connections;\n".
        "CREATE TABLE connections (object INT, with INT);\n\n";
$flag = 0;
@fields = split ', ', $workshops_workshop_format;
$newid = 0;
foreach (@no_comments) {
    $flag = 0 if /^\\\.$/;
    s/\n//g;
    if ($flag) {
        @values = split "\t", $_;
        print "INSERT INTO objects(id, type) VALUES($newid, 2);\n";
        for ($i = 0; $i < $#values+1; $i++) {
            print "INSERT INTO strings(object, name, value) VALUES($newid, '$fields[$i]', '$values[$i]');\n";
            $workshops_id[$values[$i]] = $newid if $fields[$i] eq 'id';
        }
        print "\n";
        $newid++;
    }
  $_;$flag = 1 if /^COPY workshops_workshop/;
}
$flag = 0;
@fields = split ', ', $applications_applicant_format;
print "\n";
foreach (@no_comments) {
    $flag = 0 if /^\\\.$/;
    s/\n//g;
    if ($flag) {
        @values = split "\t", $_;
        print "INSERT INTO objects(id, type) VALUES($newid, 1);\n";
        for ($i = 0; $i < $#values+1; $i++) {
            print "INSERT INTO strings(object, name, value) VALUES($newid, '$fields[$i]', '$values[$i]');\n";
            $applicants_id[$values[$i]] = $newid if $fields[$i] eq 'id';
        }
        print "\n";
        $newid++;
    }
  $flag = 1 if /^COPY applications_applicant/;
}
$flag = 0;
@fields = split ', ', $workshops_application_format;
foreach (@no_comments) {
    $flag = 0 if /^\\\.$/;
    s/\n//g;
    if ($flag) {
        @values = split "\t", $_;
        for ($i = 0; $i < $#values+1; $i++) {
            $workshop = $values[$i] if $fields[$i] eq 'workshop_id';
            $applicant = $values[$i] if $fields[$i] eq 'applicant_id';
        }
        print "INSERT INTO connections(object, with) VALUES($workshops_id[$workshop], $applicants_id[$applicant]);\n";
    }
  $_;$flag = 1 if /^COPY workshops_application/;
}
print ".quit\n";

