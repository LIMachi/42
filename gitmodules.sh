if [ -z $1 -o -z $2 -o -z $3 -o -z $4 ]
then
	echo 'help'
	exit 0
fi

BASE_REPO_URL=$1
BRANCH=$2
FOLDER=$3
NEW_REPO_URL=$4

LPWD=$PWD
echo $LPWD
WORK_PATH='/tmp/.tmpgitmodule'
rm -rf $WORK_PATH
git clone $BASE_REPO_URL $WORK_PATH
cd $WORK_PATH
git filter-branch --prune-empty --subdirectory-filter $FOLDER $BRANCH
git remote set-url origin $NEW_REPO_URL
git push --force -u origin $BRANCH
cd $LPWD
echo $PWD
git rm -rf $FOLDER
rm -rf $FOLDER
git submodule add --force $NEW_REPO_URL
git submodule init
git submodule update
cd $FOLDER
git checkout $BRANCH
cd $LPWD
