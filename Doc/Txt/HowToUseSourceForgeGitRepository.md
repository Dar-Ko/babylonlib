# How to Use SourceForge Git Repository

## How to Add a New Project Member

To add a project member to a [**SourceForge**](https://sourceforge.net/ "The Complete Software Platform") repository, you must have **Administrator** rights for that project.

### Adding a New Member

1.  **Navigate** to the main page of your project on [**SourceForge**](https://sourceforge.net/ "The Complete Software Platform").
    
    - Go to [**SourceForge**](https://sourceforge.net/ "The Complete Software Platform") ▸ Login ▸ 'Me ▾' and select select the *project name*.
    - On project’s front page and click the **Admin** button in the top navigation bar.
2.  **Click** the 'User Permissions\*\*'\*\* menu item located on the left side.
    
    - In the right pane are default groups with roles of **Admin**, **Developer**, and **Member**
        - **Admin:** Full control over the project and tools.
        - **Developer:** Read and write access to project tools (like the repository).
        - **Member:** Generally lower permissions than developers, though these can be customized.
    - Choose the role for the new member and click on '+Add'.
    - Type the SourceForge username, and click **Save**. This implies that a collaborator must have a SourceForge account.

### Managing Existing Members

To change a user's role, add them to the new group first using the steps above, then click the '**\-'** (minus) icon next to their name in their previous group to remove those old permissions.

- **Custom Permissions:** You can create **Custom Groups** for specific teams (e.g., "Documentation") and assign them unique tool-level access.
- **Tool-Specific Access:** If you need to restrict access to just the repository, go to **Admin ▸ Tools**, find your code tool (e.g., Git), and click **Permissions** to adjust which groups can read or write.

* * *

## Update eMail address

- [**Log in**](https://sourceforge.net/auth/ "Login") to your account on [SourceForge](https://sourceforge.net/auth/ "Login").
- Click on 'Me ▾' **▸** 'Account Settings' **▸** Preferences
- Scroll down to the 'Email Address' section, enter your new email Address in the provided field.
- Click on 'Claim New Address' and wait for a verification message on the new address.
- Select the old address and click Delete button and Save button.

* * *

## Set up SSH key

- Open PowerShell or Command Prompt and run the command:  
    `ssh-keygen -t ed25519 -C "your_sourceforge_username"`
- Press Enter to accept the default save location (path on Windows is  `C:\Users\YourName\.ssh\id_ed25519`).  
    Enter a secure passphrase when prompted (recommended) or press Enter twice for no passphrase.
- [**Log in**](https://sourceforge.net/auth/ "Login") to [SourceForge](https://sourceforge.net/auth/ "Login"). Click on 'Me ▾' ▸ 'Account Settings' ▸ 'SSH Settings'.
- Go to your `.ssh` folder: `cd ~/.ssh`.  
    *Note*: on **Windows** replace <ins>home directory</ins> shortcut `~` with `C:\Users\YourName\`).  
    Copy the entire content of the public key file (`id_ed25519.pub`) to 'SSH Public Keys:' text box on the [SourceForge Shell Services Configuration](https://sourceforge.net/auth/shell_services) page from the previous step.
- Update your SourceForge entry in `~/.ssh/config` to explicitly enforce the rules below:
    
    ```text
    # Replace 'YOUR_USERNAME' with your actual SourceForge account username
    # On Windows replace ~/ with C:\Users\YOUR_USERNAME\
    Host sf git.code.sf.net shell.sourceforge.net frs.sourceforge.net
        HostName %h
        User YOUR_USERNAME
        IdentityFile ~/.custom/id_ed25519
        IdentitiesOnly yes
        PubkeyAuthentication yes
        # If your local network, corporate firewall, or ISP blocks outbound SSH on
        # port 22, SourceForge offers tunnel over HTTPS port 443
        #Port 443
        # Save the passphrase for the subsequent usage
        AddKeysToAgent yes
    ```
    
    Make sure file permissions are locked down. Run `chmod 700 ~/.ssh` and `chmod 600 ~/.ssh/custom/*` to keep OpenSSH from silently rejecting the directory.
    
- After waiting a few minutes for the keys to sync, test your connection by running the command:  
    `ssh -T USERNAME@shell.sourceforge.net`.  
    To troubleshot, run a direct network test and force verbose diagnostics:  
    - Run `nc -zv git.code.sf.net 22` or `curl -I https://sf.net` to ensure SourceForge's servers are answering you at all.
    - Run `ssh -vvv YOUR_USERNAME@git.code.sf.net`. If it hangs permanently at `"Connecting to git.code.sf.net..."`, your local router, firewall, or ISP is dropping the packet.

* * *

The error `fatal: Interactive git shell is not enabled` happens because you ran a bare interactive login command like `ssh git.code.sf.net`. SourceForge intentionally blocks direct command-line shell access on their Git servers for security reasons.

Try cloning your project repository directly using your terminal:  
`<span style="color: rgb(255, 255, 255);">git clone ssh://YOUR_USERNAME@git.code.sf.net/p/YOUR_PROJECT/YOUR_REPO</span>`

* * *

## Working with SourceForge repository

To push and commit to your SourceForge repository, you will use standard Git commands on your local machine.

### Initialize and Link Your Local Repository

If you have not already linked your local code folder to SourceForge, navigate to your project folder in your terminal and run these commands:

```bash
# Initialize git if you haven't already
git init

# Link your local folder to your SourceForge repository
# (Replace USERNAME, PROJECT, and REPO with your actual SourceForge details)
git remote add origin ssh://USERNAME@git.code.sf.net/p/PROJECT/REPO

```

*Note*: If you already have a remote named "origin" and need to update it, run  
`git remote set-url origin ssh://USERNAME@git.code.sf.net/p/PROJECT/REPO`  
instead.

To find your exact `PROJECT` and `REPO` values, look at the URL of your project's code page on the SourceForge website. SourceForge assigns these based on how you registered your project.

- **`PROJECT`**: This is your project's unique **UNIX short name**. It is the lowercase, hyphenated name used in your project's website URL (e.g., if your project is `https://sourceforge.net`, your `PROJECT` name is `my-cool-app`).
- **`REPO`**: This is the specific name of your Git repository slot. By default, when you add a Git tool to a SourceForge project, it automatically names it **`code`**.

You can copy the exact string directly from your SourceForge project dashboard:

1.  Log into **SourceForge** and go to your project's main page.
2.  Click on the **Code** tab (or whatever you named your Git repository tool).
3.  Look at the top of the page for the **Read/Write** SSH connection string.  
    It will display the ready-to-use command, which looks exactly like this:  
    `ssh://username@git.code.sf.net/p/project-name/code`

### Stage and Commit Your Changes

Save your work locally by staging the files and creating a commit snapshot:

```bash
# 1. Stage all new and modified files
git add .

# 1.1. Preview what is staged (optinal)
git status

# 2. Commit the snapshot locally with a descriptive message
git commit -m "Your descriptive commit message here"

```

To preview what is staged check the status. Staged files will be listed in **green** under the heading `"Changes to be committed"`.  
If you have a lot of changes and just want a clean list of the names of the files that are staged, use:   
`git diff --name-only --cached`.  
To review the actual lines of code that you staged before you commit them, run:   
`git diff --staged`. Alternatively, `git diff --cached` does the exact same thing.

### Push to SourceForge

Send your local commits to the remote SourceForge servers:

```bash
# Push your current branch (usually 'main' or 'master') to SourceForge
git push -u origin master

# Push to SourceForge only (if POJECT/.git/cofig has [remote "SourceForge"] section)
git push SourceForge master
```

If your local branch is named `main`, use `git push -u origin main` instead.

**Verify the Push  
**Once the upload finishes, you can verify it worked:

- Run `git status` to ensure your local working directory is completely clean.
- Refresh your project's **Code** tab on the SourceForge website to see your updated files and commit history

### Pull / Fetch Updates

When working with a team or pulling down changes you made from another computer, specify the source platform:

```bash
# Pull latest updates from GitHub into your local branch
git pull GitHub master

# Pull latest updates from SourceForge into your local branch
git pull SourceForge master

```

### Check Your Remote Status

You can verify that Git sees paths correctly at any time by running:  
`git remote -v`
