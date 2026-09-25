## Introduction

To use a specific credentials file (private key) to SSH into a server from Ubuntu, you use the `-i` flag (Identity File):  
`ssh -i /path/to/your/private_key username@remote_host`  
*Note*: If your key file permissions are too open, SSH will reject it. Fix it by running: `chmod 600 /path/to/your/private_key`.

Also, you can map the credential file to a specific server using your local SSH config file:  
`nano ~/.ssh/config`  
and append the server configuration section

```conf
Host myserver
    HostName 192.168.1.50
    User USERNAME
    IdentityFile ~/.ssh/my_custom_key
```

## Buffalo LinkStation LS-WVL

You cannot SSH as a regular USERNAME or the `admin` account because of how Buffalo designed the firmware's underlying Linux operating system.  
The `admin` username you use to log into the NAS web browser interface is **not a true Linux system account.** Buffalo's system architecture isolates the web administration tool from terminal access. The web server translates your commands behind a graphical wrapper, but the operating system itself does not grant the `admin` alias a shell terminal environment (`/bin/sh` or `/bin/bash`).

Buffalo's firmware completely wipes the `/root` filesystem upon reboot. If you want any configuration file to survive a NAS power cycle, you must map the folder to your storage array using a symlink before restarting the device.  
Other solution is to use a **modified custom firmware** image like *Shonk's Mod*.

### Regular Users Have No Shell (`/bin/false`)

When you create standard user accounts via the Buffalo Web UI for file sharing (SMB/AFP), the firmware explicitly disables terminal access for security. If you look at the system's user registry file `/etc/passwd`, you will find that Buffalo maps every user account to a non-interactive shell placeholder:  
`username:x:1001:1001:NAS User:/home/USERNAME:/bin/false`  
Because their login shell is mapped to `/bin/false` (or `/sbin/nologin`), the SSH daemon instantly closes the connection the moment a user authenticates.

Buffalo devices do not natively ship with SSH enabled. Because SSH on a LinkStation is typically forced open using custom exploit tools (like `ACP Commander`) or via a hidden SFTP flag edit, the underlying OpenSSH server configuration (`/etc/sshd_config`) is tailored to only map authentication privileges to the master root system user.  
Using this tools allows you to log in as `root`.

If you want a standard user to have terminal access temporarily, run this command **as root** to give them a valid Linux shell:  
`chsh -s /bin/sh USERNAME`  
Note: Buffalo's firmware will revert this shell modification back to `/bin/false` the next time the NAS reboots.

### SSH public keys

SSH public keys aren't saved as separate individual files on the server; they are strings appended as single lines inside a single file: `/root/.ssh/authorized_keys`. You can pull the file for examination by applying the legacy cipher rules to `scp` command:  
`scp -o KexAlgorithms=+diffie-hellman-group1-sha1 root@NAS_IP:/root/.ssh/authorized_keys ~/.ssh/buffalo_authorized_keys_backup`  
or inside your active SSH session on the NAS, run:  
`cat /root/.ssh/authorized_keys`.

To remove a specific key, you must edit that file. SSH into the Buffalo NAS as `root`, pen the keys file using `vi`:  
`vi /root/.ssh/authorized_keys`.  
Navigate to the line with the unused key, type **`dd`** to delete that entire line.  
Save and exit by typing **`:wq`** and pressing `Enter`.

Insure the proper folder permissions on SSH server:

```bash
chmod 700 /root
chmod 700 /root/.ssh
chmod 600 /root/.ssh/authorized_keys
```

Make your local client Ubuntu user profile to automatically use Buffalo legacy parameters, edit your local SSH config file:  
`nano ~/.ssh/config` (or on MATE desktop `pluma ~/.ssh/config`).  
Append the following configuration block:

```config
Host buffalo-nas-name
    HostName <NAS_IP>
    User root
    KexAlgorithms +diffie-hellman-group1-sha1
    PubkeyAcceptedKeyTypes +ssh-rsa
```

To verify it works use command: `ssh buffalo-nas`.

If you set client's `host` file to resolve NAS IP address to &lt;NAS_NAME&gt;, the block will be similar to the next example:

```config
# Configuration for SMB1 Buffalo NAS
Host 192.168.1.50 NAS_NAME NAS_NAME.local
    HostName %h
    User root
    IdentityFile ~/.cert/id_rsa
    KexAlgorithms +diffie-hellman-group1-sha1
    HostKeyAlgorithms +ssh-rsa
    PubkeyAcceptedAlgorithms +ssh-rsa
    ForwardX11 no
    ForwardAgent no
    Port 22
```

You can now run any of these terminal variations cleanly from your local client user space without hitting a password prompt:

```bash
ssh NAS_NAME
ssh NAS_NAME.local
ssh 192.168.1.50
```

### Debugging

If it is still dropping back to a password prompt, it means either your Ubuntu client isn't offering your specific private key file, or the Buffalo NAS is actively rejecting it due to file permissions.  
Run the connection command with the **verbose debug flag** (`-v`) to see the source of the problem:

`ssh -v NAS_NAME`  
The critical information will appear right before password prompt:

- `debug1: Will attempt key: /home/USER/.ssh/id_rsa RSA ...` # This proves your Ubuntu client successfully located and offered your private key.
- `debug1: Authentications that can continue: publickey,password` # If you see this *after* the key is offered, your Buffalo NAS is rejecting the key file. This confirms you need to run the `chmod 700 /root && chmod 600 /root/.ssh/authorized_keys` command inside the NAS to fix its internal directory permissions.
