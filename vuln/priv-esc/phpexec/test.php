<?php
shell_exec("echo \"int main()
{
    write(1, \\\"pwned\\\\n\\\", 6);
}\" > exploit.c");
?>
