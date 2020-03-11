#!/bin/bash
# gebruiker geeft username zo niet dan wordt default username gehanteerd
echo 'Geef een gebruikersnaam: '

read usr

if [[ $usr == "" ]]; then
    usr=$(whoami)   
fi

echo 'Je gebruikersnaam is' $usr


# gebruiker geeft wachtwoord op moet min 8 tekens zijn en 2x overeenkomen
echo 'Geef nu een wachtwoord op: '

while [ true ] 
do
    read psswd1
    read psswd2
    if [[ $psswd1 != $psswd2 ]]; then
        echo 'Voer hetzelfde wachtwoord in bestaande uit minimaal 8 karakters!'
    else
        break
    fi  
done

# aanmaken passwordfile
touch login.txt
touch passwordfile.txt

printf "Username: \n$usr\n\nPassword: \n" >> login.txt

printf $psswd1 >> passwordfile.txt

uitkomst=$(echo -n passwordfile.txt | md5sum) 
printf $uitkomst >> login.txt

echo 'Je account is aangemaakt en te vinden in login.txt'