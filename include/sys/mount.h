#pragma once

int mount(const char* source, const char* target, const char* type, unsigned long flags,
          const void* data);
int umount(const char* target);