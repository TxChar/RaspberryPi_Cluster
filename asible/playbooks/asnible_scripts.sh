#!/bin/bash
ansible-playbook ans01_sync_time.yml
ansible-playbook ans02_mount-drive.yml
ansible-playbook ans03_setting_nfs_head.yml
ansible-playbook ans04_setting_nfs_compute.yml
ansible-playbook ans05_seting_slurm_head.yml
ansible-playbook ans06_setting_cgroup_head.yml
ansible-playbook ans07_setting_cgroup_slurm_compute.yml