#include "types.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"
#include "user.h"

static int getCwd(char* resPath);
static char* upDir(int inode, char* ancestor, char* resPath);
static int dirLookUp(int fd, int inode, char* p);

#define NULL   ((void*)0)
#define FALSE  (0)
#define TRUE   (1)
#define PATH_SEPARATOR   "/"

int main(int argc, char *argv[]) {
  char resPath[512];
  if (getCwd(resPath))
    printf(1, "%s\n", resPath);
  else
    printf(2, "Nah doesnt Work");
  exit();
}

static int getCwd(char* resPath) {
  resPath[0] = '\0';
  char ancestor[512];

  strcpy(ancestor, ".");

  struct stat st;
  if (stat(ancestor, &st) < 0){
    return FALSE;
  }

  char* p = upDir(st.ino, ancestor, resPath); // Rekursif ke root
  if (p == NULL){
    return FALSE;
  }
  if (resPath[0] == '\0'){
    strcpy(resPath, PATH_SEPARATOR);
  }
  return TRUE;
}

static char* upDir(int inode, char* ancestor, char* resPath) {
  strcpy(ancestor + strlen(ancestor), PATH_SEPARATOR "..");
  struct stat st;
  if (stat(ancestor, &st) < 0)
    return NULL;

  if (st.ino == inode) {
    // Udh di root
    return resPath;
  }

  char* foundPath = NULL;
  int fd = open(ancestor, O_RDONLY);
  if (fd >= 0) {
    char* p = upDir(st.ino, ancestor, resPath);
    if (p != NULL) {
      strcpy(p, PATH_SEPARATOR);
      p += sizeof(PATH_SEPARATOR) - 1;

      // Cari Current Directory bois
      if (dirLookUp(fd, inode, p))
        foundPath = p + strlen(p);
    }
    close(fd);
  }
  return foundPath;
}

static int dirLookUp(int fd, int inode, char* p) {
  struct dirent de;
  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0)
      continue;
    if (de.inum == inode) {
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = '\0';
      return TRUE;
    }
  }
  return FALSE;
}
