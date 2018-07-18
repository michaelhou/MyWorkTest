

function create_crend()
{
	mkdir -p ~/.ssh
	cd ~/.ssh
cat > id_gitv2 << "EOLL"

-----BEGIN RSA PRIVATE KEY-----
MII
........
krh
-----END RSA PRIVATE KEY-----

EOLL

cat >> config << "EOLL"
####################################git_sync_v2
host gitv2
hostname XX.XX.XX.XX
user git
port XXXX 
identityfile ~/.ssh/id_gitv2
####################################git_sync_v2 end
EOLL



chmod og-rwx -R ~/.ssh

ssh -o StrictHostKeyChecking=no gitv2  'echo hello from $$;exit'

}

if [  -f ~/.ssh/config  ];then


	cat ~/.ssh/config |grep -q -E 'git_sync_v2'

	if [ $? -eq 0 ];then
		echo crendential ok..
	else
		echo credential not exist...
		create_crend
	fi

else
	echo credential not exist now start create...
	create_crend

fi
ssh -o StrictHostKeyChecking=no gitv2  'echo hello from $$;exit'

    
echo 'gitv2:~/factory.git'