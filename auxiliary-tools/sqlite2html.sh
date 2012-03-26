#!/bin/bash

if [[ -z "$1" ]]; then
    echo "Usage: sqlite2html database > output.html"
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
    table.object.Group {
    background: #99FF66;
   }
    table.object.Event {
    background: #699EF7;
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

objects=$(sqlite3 -list $1 "SELECT id, type FROM objects;")

while [[ -n "$objects" ]]; do
    object=$(echo "$objects" | sed 1q)
    objects=$(echo "$objects" | sed 1d)
    id=$(echo "$object" | sed 's/|.*//')
    type=$(echo "$object" | sed 's/.*|//')
    case $type in
    1)
        echo "   <table class='object Person' id=$id>"
        ;;
    2)
        echo "   <table class='object Group' id=$id>"
        ;;
    3)
        echo "   <table class='object Event' id=$id>"
        ;;
    *)
        echo "   <table class='object unknown' id=$id>"
        ;;
    esac
    echo "    <tr><th colspan=2>#$id</th></tr>"
    strings=$(sqlite3 -list $1 "SELECT name, value FROM strings WHERE object=$id;")
    while [[ -n "$strings" ]]; do
        string=$(echo "$strings" | sed 1q)
        strings=$(echo "$strings" | sed 1d)
        name=$(echo "$string" | sed 's/|.*//')
        value=$(echo "$string" | sed 's/.*|//')
        echo "    <tr><th>$name</th><td class=value>$value</td></tr>"
    done
    times=$(sqlite3 -list $1 "SELECT name, value FROM times WHERE object=$id;")
    while [[ -n "$strings" ]]; do
        time=$(echo "$times" | sed 1q)
        times=$(echo "$times" | sed 1d)
        name=$(echo "$time" | sed 's/|.*//')
        value=$(echo "$time" | sed 's/.*|//')
        echo "    <tr><th>$name</th><td class=value>$value</td></tr>"
    done
    case $type in
    1)
        echo "    <tr><th>groups</th><td class=value><ul>"
        connections=$(sqlite3 -list $1 "SELECT id FROM objects WHERE type=2 AND id IN ((SELECT object FROM connections WHERE with=$id),(SELECT with FROM connections WHERE object=$id));")
        while [[ -n "$connections" ]]; do
            connection=$(echo "$connections" | sed 1q)
            connections=$(echo "$connections" | sed 1d)
            echo "     <li><a href=#$connection>#$connection</a></li>"
        done
        echo "    </ul></td></tr>"
        ;;
    2)
        echo "    <tr><th>people</th><td class=value><ul>"
        connections=$(sqlite3 -list $1 "SELECT id FROM objects WHERE type=1 AND (id IN (SELECT object FROM connections WHERE with=$id) OR id IN (SELECT with FROM connections WHERE object=$id));")
        while [[ -n "$connections" ]]; do
            connection=$(echo "$connections" | sed 1q)
            connections=$(echo "$connections" | sed 1d)
            echo "     <li><a href=#$connection>#$connection</a></li>"
        done
        echo "    </ul></td></tr>"
        echo "    <tr><th>children_groups</th><td class=value><ul>"
        connections=$(sqlite3 -list $1 "SELECT id FROM objects WHERE type=2 AND id IN (SELECT with FROM connections WHERE object=$id);")
        while [[ -n "$connections" ]]; do
            connection=$(echo "$connections" | sed 1q)
            connections=$(echo "$connections" | sed 1d)
            echo "     <li><a href=#$connection>#$connection</a></li>"
        done
        echo "    </ul></td></tr>"
        echo "    <tr><th>parent_groups</th><td class=value><ul>"
        connections=$(sqlite3 -list $1 "SELECT id FROM objects WHERE type IN (2, 3) AND id IN (SELECT object FROM connections WHERE with=$id);")
        while [[ -n "$connections" ]]; do
            connection=$(echo "$connections" | sed 1q)
            connection=$(echo "$connections" | sed 1d)
            echo "     <li><a href=#$connection>#$connection</a></li>"
        done
        echo "    </ul></td></tr>"
        ;;
    3)
        echo "    <tr><th>people</th><td class=value><ul>"
        connections=$(sqlite3 -list $1 "SELECT id FROM objects WHERE type=1 AND (id IN (SELECT object FROM connections WHERE with=$id) OR id IN (SELECT with FROM connections WHERE object=$id));")
        while [[ -n "$connections" ]]; do
            connection=$(echo "$connections" | sed 1q)
            connections=$(echo "$connections" | sed 1d)
            echo "     <li><a href=#$connection>#$connection</a></li>"
        done
        echo "    </ul></td></tr>"
        echo "    <tr><th>children_groups</th><td class=value><ul>"
        connections=$(sqlite3 -list $1 "SELECT id FROM objects WHERE type=2 AND id IN (SELECT with FROM connections WHERE object=$id)")
        while [[ -n "$connections" ]]; do
            connection=$(echo "$connections" | sed 1q)
            connections=$(echo "$connections" | sed 1d)
            echo "     <li><a href=#$connection>#$connection</a></li>"
        done
        echo "    </ul></td></tr>"
        ;;
    *)
        ;;
    esac
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

