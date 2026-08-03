# Configuring SSH access on a Windows box

1.  Figure out if you are an Administrator on Windows  
    Windows handles SSH keys completely differently depending on your account level.  
    a) Log into your Windows box  
    Open PowerShell and run this:
    
    ```powershell
    # If this outputs your username, you are an Administrator
    whoami /groups | Select-String "Administrators"
    ```
    
    or b) use SSH:  
    `ssh username@remote_windows_ip` and in the remote Windows SSH prompt type
    
    ```cmd
    powershell -Command "whoami /groups | Select-String 'Administrators'"
    ```
    
2.  Push the Key Manually
    
    - If the remote Windows user is a **Standard User**  
        Copy your public key text into `C:\Users\username.ssh\authorized_keys`
        
        ```bash
        # 1. Ensure the remote .ssh folder exists on Windows
        #    Enter your Windows password when prompted
        ssh username@remote_windows_ip "mkdir C:\Users\username\.ssh"
        
        # 2. Securely copy the public key file over to Windows via SCP
        scp /path/to/.cert/my_custom_key.pub username@remote_windows_ip:C:/Users/username/.ssh/authorized_keys
        ```
        
    - If the remote Windows user is an **Administrator**  
        Windows enforces a strict security policy for admins. Run this from your local terminal:
        
        ```bash
        # 1. Upload your public key to a temporary location on Windows
        scp /path/to/.cert/my_custom_key.pub username@remote_windows_ip:C:/Users/username/AppData/Local/Temp/temp_key.pub
        
        # 2. Log into the Windows machine normally using your password
        ssh username@remote_windows_ip
        ```
        

Once you are logged into the Windows SSH prompt, append the key to the master administrator file and lock down its file permissions correctly:

```bash
powershell -Command "Add-Content -Path 'C:\ProgramData\ssh\administrators_authorized_keys' -Value (Get-Content 'C:\Users\username\AppData\Local\Temp\temp_key.pub');
icacls 'C:\ProgramData\ssh\administrators_authorized_keys' /inheritance:r /grant 'Administrators:F' /grant 'SYSTEM:F' "
```

3.  Test Login  
    Once the files are written, exit your terminal and reconnect using your custom nickname from your local config file:  
    `ssh mybox`
    
