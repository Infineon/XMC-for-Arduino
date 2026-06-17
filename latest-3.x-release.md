# XMC-for-Arduino Latest 3.x Release

This branch is no longer the main development branch. The main branch is now for version 4.x.
This branch will only be maintained for bug fixes and security patches. 
New features will be added to the 4.x branch.

The `arduino-devops` based `release.yml` workflow is not working straightforwardly for this branch.

In order to release a new version of the 3.x branch, you need to follow these manual steps:

1. After merging the PR into `master-2.x-3.x`, you need to create a new tag from the master HEAD. The tag should follow the format `3.x.y`, following the sematic versioning rules.
2. After creating the tag, you need to push it to the remote repository. You can do this using the following command:

   ```bash
   git push origin <tag_name>
   ```

3. This will trigger the `release.yml` workflow, which will build a `package_infineon_index.json` file and the `XMC-for-Arduino-3.x.y.zip` package. Go to the release page and download the `package_infineon_index.json` file and the `XMC-for-Arduino-3.x.y.zip` package for the new version. That `json` file is only containing the latest release, but not the history of the previous release.
4. There is a `latest-3.x` release, download from there the `package_infineon_index.json` file. This file contains all the previous releases of the 3.x branch. 
5. You need to merge the new `package_infineon_index.json` file with the previous one, so that the new release is added to the list of previous releases. This will be the new `package_infineon_index.json` file that we will upload to the `latest-3.x` release.
6. Remove the current tag `latest-3.x` from the remote, and assign that same tag to the new release tag. You can do this using the following commands:

   ```bash
   git push --delete origin latest-3.x
   git tag -d latest-3.x
   git tag latest-3.x 
   git push origin latest-3.x
   ```

7. Once the new release has been created in the release section, you can update the `package_infineon_index.json` file in the `latest-3.x` release with the new merged file, and also the `XMC-for-Arduino-3.x.y.zip` package for the new version, which you downloaded in the previous step. Make sure you delete first the existing files in the release before uploading the new ones. 
If the following url is used in the Arduino IDE to install the XMC-for-Arduino package:
    ```
    https://github.com/Infineon/XMC-for-Arduino/releases/download/latest-3.x/package_infineon_index.json
    ```
    it will show all the releases of the 3.x (and 2.x)version, including the new one that you just released:


> [!IMPORTANT]

1. Make sure that the the release marked as latest is the latest 4.x release from the `master` branch. For that, in the release section, look for the highest 4.x.y release, and mark it as the latest release by clicking on the "Edit" button of that release, then checking the "latest" checkbox, and then saving the changes. This will ensure that the latest release is always the latest 4.x release, and not the latest 3.x release. *Otherwise, the 4.x release won't be shown in the Arduino IDE, and users will only see the 3.x releases, which is not what we want.*

