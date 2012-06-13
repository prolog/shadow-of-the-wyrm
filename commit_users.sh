hg log | grep '^user\?'|cut -d':' -f2|sort|uniq -c|sort -nr
