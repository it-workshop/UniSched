#!/bin/bash

if [[ -z "$1" ]]; then
    echo "Usage: yaml2html.sh database.yaml > output.html"
    exit
fi

cat << EOF
<!DOCTYPE html>
<html>
 <head>
  <title>$1</title>
  <meta charset=utf8>
  <style>
  table.object {
    display: inline-block;
    width: 300px;
    height: 300px;
    background: snow;
    padding: 5px;
    margin: 5px;
    border-radius: 5px;
    font: 10pt Verdana;
  }
  table.object td,th {
    width: 150px;
  }
  table.object td.value ul {
    list-style-type: none;
  }
  table.object:target {
    background: silver;
  }
  </style>
 </head>
 <body>
  <header>
   <h1>$1</h1>
   <hr>
  </header>
  <section>
EOF

echo "   <!-- Reading $1 --!>"
file=$(<$1)

while [[ -n "$file" ]]; do
    block=$(echo "$file" | sed '1,/^-/!d;')
    if [[ -n "$(echo "$block" | sed '/^-/!d;1d')" ]]; then
        file=$(echo -e "$(echo "$block" | sed '/^-/!d;1d')\n$(echo "$file" | sed '1,/^-/d')")
        block=$(echo "$block" | sed '$d')
    else
        file=""
    fi
    class=$(echo "$block" | sed '/^[ -] Object: /!d;s/^[ -] Object: //')
    id=$(echo "$block" | sed '/^[ -] ID: /!d;s/^[ -] ID: //')
    block=$(echo "$block" | sed '/^[ -] Object: /d;/^[ -] ID: /d;/^[ -] VCard:/d')
    vcard=$(echo "$block" | sed '/^    [^-]/!d')
    links=$(echo "$block" | sed '/^    [^-]/d')
    cat << EOF
   <table class='object $class' id='$id'>
    <tr><th colspan=2>#$id</th></tr>
EOF
    while [[ -n "$vcard" ]]; do
        line=$(echo "$vcard" | sed q)
        vcard=$(echo "$vcard" | sed 1d)
        field=$(echo "$line" | sed 's/^    //;s/:.*$//')
        value=$(echo "$line" | sed 's/^[^:]*: //')
        echo "    <tr><th class=field>$field</td><td class=value>$value</td></tr>"
    done
    while [[ -n "$links" ]]; do
        field=$(echo "$links" | sed '1!d;s/[ :]*//g')
        value=$(echo "$links" | sed '1d;1,/:/!d')
        if [[ -n "$(echo "$value" | sed '/:/!d')" ]]; then
            links=$(echo -e "$(echo "$value" | sed '$!d')\n$(echo "$links" | sed '1,/:/d')")
            value=$(echo "$value" | sed '$d')
        else
            links=""
        fi
        echo "    <tr><th class=field>$field</td><td class=value><ul>"
        while [[ -n "$value" ]]; do
            id=$(echo "$value" | sed '1!d;s/[ -]*//g')
            value=$(echo "$value" | sed 1d)
            echo "     <li><a href='#$id'>#$id</li>"
        done
        echo "    </ul></td></tr>"
    done
    echo "   </table>"
done
cat << EOF
  </section>
  <footer>
   <hr>
   $1
  </footer>
 </body>
</html>
EOF

