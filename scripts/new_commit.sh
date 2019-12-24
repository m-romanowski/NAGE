#!/bin/bash

## CONFIG ##################################################################################################################

# Main
ROOT_PATH=.
VERSION_FILENAME=VERSION
DATE_FORMAT='%y.%m.%d'
INFO_COLOR=$'\e[1;36m'
ERROR_COLOR=$'\e[1;31m'
NO_COLOR=$'\e[0m'

## Errors
BUILD_TYPE_ERROR="${ERROR_COLOR}[ERROR] Check if MAJOR, MINOR and BUILD_TYPE have been defined!${NO_COLOR}\n"

# Informations (logs)
COMMIT_COMMENT="${INFO_COLOR}Commit comment:${NO_COLOR}"

# Prompts
COMMIT_DESC_PROMPT="${INFO_COLOR}Commit description:${NO_COLOR} "
COMMIT_PROMPT="${INFO_COLOR}Add commit [yes/no]:${NO_COLOR} "
PUSH_TO_REMOTE_PROMPT="${INFO_COLOR}Push to remote repo [yes/no]:${NO_COLOR} "

############################################################################################################################

# Read version file
$ROOT_PATH $VERSION_FILENAME

# Check if variables (major, minor, build type) exists.
if [ ! -n "$MAJOR" ] || [ ! -n "$MINOR" ] || [ ! -n "$BUILD_TYPE" ]; then
    printf $BUILD_TYPE_ERROR
    exit 1
fi

# Prefix for commit comment - MAJOR.MINOR.BUILD_DATE-BUILD_TYPE, e.g. 0.1.19.04.01-dev
COMMIT_DESC_PREFIX="$MAJOR.$MINOR.$(date +$DATE_FORMAT)-$BUILD_TYPE"

# Commit description
read -p "$COMMIT_DESC_PROMPT" COMMIT_DESC
git add -A $ROOT_PATH && \
git status

# Commit
printf "$COMMIT_COMMENT $COMMIT_DESC\n"
read -p "$COMMIT_PROMPT" USER_ANSWER1
USER_ANSWER1=${USER_ANSWER1:-yes}

if [ "$USER_ANSWER1" == "yes" ]; then
    git commit -m "$COMMIT_DESC_PREFIX $COMMIT_DESC"
else
    exit 1
fi

# Push to repote git repo
git log -1

read -p "$PUSH_TO_REMOTE_PROMPT" USER_ANSWER2
USER_ANSWER2=${USER_ANSWER2:-yes}
if [ "$USER_ANSWER2" == "yes" ]; then
    git push origin master
else
    exit 1
fi
